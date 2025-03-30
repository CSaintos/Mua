#include "NumberUtils.hpp"

using namespace std;
using namespace mua;

void NumberUtils::strToNumber(string number, list<Character> &whole_number, list<Character> &less_than_zero)
{
  bool dot_met = false;
  for (char c : number)
  {
    CharacterType c_type = CharacterUtils::cC_map[c];
    if (c_type == CharacterType::DIGIT)
    {
      Character character;
      character.type = CharacterType::DIGIT;
      character.c = c;
      if (dot_met)
      {
        less_than_zero.push_back(character);
      }
      else
      {
        whole_number.push_back(character);
      }
    }
    else if (c_type == CharacterType::DOT)
    {
      dot_met = true;
    }
    else
    {
      cout << "error" << endl;
    }
  }
}

string NumberUtils::listCharToStr(list<Character> &c_list)
{
  stringstream ss;
  for (auto c : c_list)
  {
    ss << c.c;
  }
  return ss.str();
}

string NumberUtils::stripTrailingZeros(string number)
{
  list<Character> whole_number;
  list<Character> less_than_zero;

  NumberUtils::strToNumber(number, whole_number, less_than_zero);

  list<Character>::iterator itr_at_end = less_than_zero.end();
  bool loop = true;
  while (loop && !less_than_zero.empty())
  {
    itr_at_end--;
    if (itr_at_end->c == '0')
    {
      less_than_zero.pop_back();
    }
    else
    {
      loop = false;
    }
  }

  stringstream ss;
  for (auto c : whole_number)
  {
    ss << c.c;
  }
  if (!less_than_zero.empty())
  {
    ss << '.';
    for (auto c : less_than_zero)
    {
      ss << c.c;
    }
  }

  return ss.str();
}

unique_ptr<Node> NumberUtils::fractionalize(INodeFactory *node_factory, string number)
{
  list<Character> whole_number;
  list<Character> less_than_zero;
  NumberUtils::strToNumber(number, whole_number, less_than_zero);

  list<Character>::iterator itr_at_end = less_than_zero.end();
  bool loop = true;
  while (loop && !less_than_zero.empty())
  {
    itr_at_end--;
    if (itr_at_end->c == '0')
    {
      less_than_zero.pop_back();
    }
    else
    {
      loop = false;
    }
  }

  if (!less_than_zero.empty())
  {
    string whole_number_str = NumberUtils::listCharToStr(whole_number);
    string less_than_zero_str = NumberUtils::listCharToStr(less_than_zero);
    int digit_size = less_than_zero_str.length();
    int before_dot = std::stod(whole_number_str);
    int after_dot = std::stod(less_than_zero_str);
    int denominator = std::pow(10, digit_size);
    int gcd = std::gcd(after_dot, denominator);
    after_dot = after_dot / gcd;
    denominator = denominator / gcd;
    int numerator = denominator * before_dot + after_dot;
    string numerator_str = std::to_string(numerator);
    string denominator_str = std::to_string(denominator);

    Token tok_left;
    tok_left.type = TokenType::DIGIT;
    tok_left.lexemes = numerator_str;
    Token tok_right;
    tok_right.type = TokenType::DIGIT;
    tok_right.lexemes = denominator_str;
    Token tok_op;
    tok_op.type = TokenType::FSLASH;

    unique_ptr<Node> left_node = node_factory->produceNode(tok_left);
    unique_ptr<Node> right_node = node_factory->produceNode(tok_right);
    unique_ptr<Node> op_node = node_factory->produceNode(tok_op, left_node, right_node);
    return std::move(op_node);
  }
  else 
  {
    Token tok;
    tok.type = TokenType::DIGIT;
    tok.lexemes = NumberUtils::listCharToStr(whole_number);

    unique_ptr<Node> node = node_factory->produceNode(tok);
    return std::move(node);
  }

  return nullptr;
}

// if a = 7, then d < 23
// if a = 6, then d < 25
// if a = 5, then d < 28
// if a = 4, then d < 32
// if a = 3, then d < 40
// in other words, if b^e > 2^64, then bpow returns an incorrect result
unsigned long long NumberUtils::bpow(unsigned long long b, unsigned long long e)
{
  unsigned long long res = 1;
  unsigned long long i = e;
  unsigned long long a = b;
  while (i > 0)
  {
    if (i & 1) res *= a;
    a *= a;
    i>>=1;
  }
  return res;
}

unsigned long long NumberUtils::mpow(unsigned long long b, unsigned long long e, unsigned long long m)
{
  unsigned long long res = 1;
  unsigned long long base = b % m; 
  unsigned long long i = e;
  while (i > 0)
  {
    if (i & 1) res = res * base % m;
    base = base * base % m;
    i >>= 1;
  }

  return res;
}

bool NumberUtils::isPrime(const int x)
{
  int n = x;
  if (n < 0)
  {
    n *= -1;
  }
  if (n < 3) return n == 2; 
  if ((n & 1) == 0) return false;

  // the real miller-rabin test
  int k = n - 1;
  int d = k;
  int s = 0;
  int a = 2;
  while ((d & 1) == 0)
  {
    d >>= 1;
    s++;
  }
  k = 5; // number of repeats for accuracy
  int upper_a = a + k;
  int z = 0;
  int y = 0;
  bool is_prime = true;
  //cout << endl << "s = " << s << endl;

  while (is_prime &&
  a <= upper_a &&
  a <= n - 2)
  {
    //cout << "a = " << a << endl;
    //cout << "d = " << d << endl;
    //cout << "n = " << n << endl;
    //cout << "a^d = " << NumberUtils::bpow(a, d) << endl;
    //cout << "a^d % n = " << (NumberUtils::bpow(a, d) % (unsigned long long) n) << endl;
    int z = NumberUtils::mpow(a, d, n);
    //cout << "z = " << z << endl;
    for (int i = 0; i < s && is_prime; i++)
    {
      y = ((int)std::pow(z, 2)) % n;
      if (y == 1 &&
      z != 1 &&
      z != n - 1)
      {
        is_prime = false;
      }
      z = y;
    }
    if (y != 1) is_prime = false;
    a++;
  }

  return is_prime;
}

int NumberUtils::g(int x, int i, int b)
{
  if (i == 0) return x;
  return ((int)(std::pow(x, 2) + b) % i);
}

list<int> NumberUtils::factorize(int n)
{
  std::list<int> primes;
  primes.push_back(n);
  std::list<int>::iterator i = primes.begin();
  
  while (i != primes.end())
  {
    if (isPrime(*i))
    {
      ++i;
    }
    else
    {
      // 0 and 1 is neither prime nor composite
      if (*i == 0 || *i == 1) return std::list<int>();
      int p = 1;
      // if i is even, then factor out 2
      if (*i % 2 == 0)
      {
        p = 2;
      }
      else
      {
        // pollard rho algorithm
        std::unordered_map<int, int> seq_val; 
        int max_cycles = 3;
        int cycles = 0;
        // todo instead of making start_val a random value, make it = sqrt(n) using a root-finding algorithm (gtab) (precision of int)
        int start_val = 0;
        int x = start_val;
        int y = x;
        int b = 1;
        int diff = 0;
        bool is_fail = true;
        bool is_cyclical = false;

        while (is_fail && !is_cyclical)
        {
          x = start_val;
          y = x;
          p = 1;

          while (p == 1 && !is_cyclical)
          {
            x = g(x, *i, b);
            //cout << "x: " << x << endl;
            y = g(g(y, *i, b), *i, b);
            //cout << "y: " << y << endl;
            //cout << "i: " << *i << endl;
            diff = x - y == 0 ? x : x - y;
            p = std::gcd(std::abs(diff), *i);
            is_cyclical = x == y;
          }

          if (p != *i && p != 1)
          {
            is_fail = false;
          }
          //else if (p == *i)
          //{
          //  seq_val[x] = (seq_val.contains(x) ? seq_val[x] + 1 : 1);
          //  cycles = (seq_val[x] > cycles ? seq_val[x] : cycles);
          //}
          //is_cyclical = cycles >= max_cycles;
        
          is_cyclical = false;
          b++;
          start_val++;
          if (start_val > *i || b > *i - 2) is_cyclical = true;
        }
        // end of pollard rho algorithm
        if (is_fail)
        {
          primes = primes.size() < 2 ? std::list<int>() : primes;
          return primes;
        }
      }

      int q = (int)(*i / p);
      if (i == primes.begin())
      {
        primes.pop_front();
        if (p < q)
        {
          primes.push_back(p);
          primes.push_back(q);
        }
        else
        {
          primes.push_back(q);
          primes.push_back(p);
        }
        i = primes.begin();
      }
      else
      {
        std::list<int>::iterator backup = i;
        --backup;
        primes.erase(i);
        ++backup;
        if (p < q)
        {
          primes.insert(backup, q);
          --backup;
          primes.insert(backup, p);
        }
        else
        {
          primes.insert(backup, p);
          --backup;
          primes.insert(backup, q);
        }
        --backup;
        i = backup;
      }
    }
  }

  if (primes.size() < 2)
  {
    primes = std::list<int>();
  }
  else
  {
    primes.sort();
  }
  return primes;
}
