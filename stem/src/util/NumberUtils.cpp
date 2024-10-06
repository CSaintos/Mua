#include "NumberUtils.hpp"

using namespace std;
using namespace stem;

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

unique_ptr<Node> NumberUtils::fractionalize(string number)
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

    unique_ptr<Node> left_node = std::make_unique<ValueNode>(tok_left);
    unique_ptr<Node> right_node = std::make_unique<ValueNode>(tok_right);
    unique_ptr<Node> op_node = std::make_unique<FSlash>(left_node, tok_op, right_node);
    return std::move(op_node);
  }
  else 
  {
    Token tok;
    tok.type = TokenType::DIGIT;
    tok.lexemes = NumberUtils::listCharToStr(whole_number);

    unique_ptr<Node> node = std::make_unique<ValueNode>(tok);
    return std::move(node);
  }

  return nullptr;
}
