#include "NumberUtils.hpp"

using namespace std;
using namespace mua;

void NumberUtils::strToNumber(string number, list<Character> &whole_number, list<Character> &less_than_one)
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
        less_than_one.push_back(character);
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
  list<Character> less_than_one;

  NumberUtils::strToNumber(number, whole_number, less_than_one);

  list<Character>::iterator itr_at_end = less_than_one.end();
  bool loop = true;
  while (loop && !less_than_one.empty())
  {
    itr_at_end--;
    if (itr_at_end->c == '0')
    {
      less_than_one.pop_back();
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
  if (!less_than_one.empty())
  {
    ss << '.';
    for (auto c : less_than_one)
    {
      ss << c.c;
    }
  }

  return ss.str();
}

unique_ptr<Node> NumberUtils::fractionalize(INodeFactory *node_factory, string number)
{
  list<Character> whole_number;
  list<Character> less_than_one;
  string num = NumberUtils::stripTrailingZeros(number);
  NumberUtils::strToNumber(number, whole_number, less_than_one);

  if (!less_than_one.empty())
  {
    string whole_number_str = NumberUtils::listCharToStr(whole_number);
    string less_than_one_str = NumberUtils::listCharToStr(less_than_one);
    int digit_size = less_than_one_str.length();
    int before_dot = std::stod(whole_number_str);
    int after_dot = std::stod(less_than_one_str);
    int denominator = std::pow(10, digit_size);
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

int NumberUtils::toPrecision(double x)
{
  string x_str = stripTrailingZeros(std::to_string(x));
  list<Character> whole_number;
  list<Character> less_than_one;
  strToNumber(x_str, whole_number, less_than_one);
  whole_number.reverse();
  less_than_one.reverse();
  x_str = listCharToStr(less_than_one);
  return x_str.empty() ? 0 : stod(x_str);
}

template<typename T>
int NumberUtils::sign(T val)
{
  return (T(0) < val) - (val < T(0));
}

double NumberUtils::radicalFunction(double x, int e, int b)
{
  return std::pow(x, e) - (double)b;
}

array<int, 2> NumberUtils::findRadicalInterval(function<double(double)> f)
{
  array<int, 2> interval = {};
  int x = interval[0];
  bool found_lower_bounds = false;
  bool found_upper_bounds = false;

  while (!(found_lower_bounds && found_upper_bounds))
  {
    if (sign(f(x)) < 0)
    {
      interval[0] = x;
      found_lower_bounds = true;
      x++;
    }
    else if (sign(f(x)) >= 0)
    {
      interval[1] = x;
      found_upper_bounds = true;
      x--;
    }
  }

  return interval;
}

double NumberUtils::GTAB(std::function<double(double)> f, double x1, double x2, double eps)
{
  double y1 = f(x1), y2 = f(x2);
  double x0 = x1; // abscissa of prev itr
  int side = 0; 
  int precision = toPrecision(eps);
  int N = (int)(std::log2(precision)) / 2 + 1; // Expected num of iters
  int n = N * 10; // Max num of iters
  bool bisection = true; 
  double x3, y3;

  for (int i = 1; i <= n; i++)
  {
    if (bisection) // bisection algorithm
    {
      x3 = (x1 + x2) / 2; // midpoint abscissa
      y3 = f(x3);
      double ym = (y1 + y2) / 2;
      if (std::abs(ym - y3) < 0.25 * (std::abs(ym) + std::abs(y3)))
      {
        bisection = false;
      }
    }
    else // False-position algorithm
    {
      x3 = (x1 * y2 - y1 * x2) / (y2 - y1);
      y3 = f(x3);
    }

    if (y3 == 0 || std::abs(x3 - x0) <= eps) // convergence check
    {
      return x3;
    }

    x0 = x3;
    if (side == 1) // Anderson-Bjork mod for side 1
    {
      double m = 1 - y3 / y1;
      if (m <= 0) y2 /= 2;
      else y2 *= m;
    }
    else if (side == 2) // Anderson-Bjork mod for side 2
    {
      double m = 1 - y3 / y2;
      if (m <= 0) y1 /= 2;
      else y1 *= m;
    }

    if (sign(y1) == sign(y3)) // if left interval = no change sign
    {
      if (!bisection) side = 1;
      x1 = x3;
      y1 = y3;
    }
    else // if right interval = no change sign
    {
      if (!bisection) side = 2;
      x2 = x3;
      y2 = y3;
    }

    if (i % N == 0) // if expected num of itr is exceeded
    {
      bisection = true;
      side = 0;
    }

  }
  return x3;
}

double NumberUtils::findRadical(const int radicand, const int root)
{
  std::function<double(double)> f = [root, radicand](double x)
  {
    return radicalFunction(x, root, radicand);
  };
  // Issue here I think
  array<int, 2> interval = findRadicalInterval(f);

  return GTAB(f, interval[0], interval[1], 0.000001);
}
