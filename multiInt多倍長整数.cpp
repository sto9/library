//a<b a,bは非負
bool CompareP(string a, string b)
{
  if (a.length() != b.length())
    return a.length() < b.length();
  rep(i, a.length())
  {
    if (a[i] != b[i])
      return a[i] < b[i];
  }
  return false;
}

//a+b a,bは非負
string AddP(string a, string b)
{
  reverse(all(a));
  reverse(all(b));
  string res;
  int up = 0;
  rep(i, max(a.length(), b.length()))
  {
    int ai, bi;
    ai = i < a.length() ? (int)(a[i] - '0') : 0;
    bi = i < b.length() ? (int)(b[i] - '0') : 0;
    int t = ai + bi + up;
    if (up == 1)
      up = 0;
    if (t >= 10)
    {
      up = 1;
      t -= 10;
    }
    res.push_back((char)(t + '0'));
  }
  if (up > 0)
    res.push_back('1');

  reverse(all(res));
  return res;
}

//a-b a,bは非負
string SubstractP(string a, string b)
{
  bool minus = CompareP(a, b);
  if (minus)
    swap(a, b);

  reverse(all(a));
  reverse(all(b));
  string res;
  int down = 0;
  rep(i, a.length())
  {
    int ai, bi;
    ai = i < a.length() ? (int)(a[i] - '0') : 0;
    bi = i < b.length() ? (int)(b[i] - '0') : 0;
    int t = ai - bi - down;
    if (down == 1)
      down = 0;
    if (t < 0)
    {
      down = 1;
      t += 10;
    }
    res.push_back((char)(t + '0'));
  }
  while (*res.rbegin() == '0' && res.length() > 1)
    res.pop_back();
  if (minus)
    res.push_back('-');
  reverse(all(res));
  return res;
}

string Add(string a, string b)
{
  string res;
  if (a[0] != '-' && b[0] != '-')
    res = AddP(a, b);
  else if (a[0] == '-' && b[0] != '-')
    res = SubstractP(b, a.substr(1));
  else if (a[0] != '-' && b[0] == '-')
    res = SubstractP(a, b.substr(1));
  else
    res = "-" + AddP(a.substr(1), b.substr(1));
  return res;
}

string Substract(string a, string b)
{
  string res;
  if (b[0] != '-')
    res = Add(a, "-" + b);
  else
    res = Add(a, b.substr(1));
  return res;
}