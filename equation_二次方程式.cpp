// Ax^2 + Bx + C = 0
// 解の個数(無数にある場合3)、解
using Real = double;
tuple<int, Real, Real> solve(Real A, Real B, Real C)
{
  if (fabs(A) < EPS)
  {
    if (fabs(B) < EPS)
    {
      if (fabs(C) < EPS)
        return {3, 0, 0};
      else
        return {0, 0, 0};
    }
    Real ans = -C / B;
    return {1, ans, 0};
  }
  Real D = B * B - 4.0 * A * C;
  if (D < 0)
    return {0, 0, 0};
  Real ans1;
  if (B > 0)
    ans1 = (-B - sqrtl(D)) / 2.0 / A;
  else
    ans1 = (-B + sqrtl(D)) / 2.0 / A;
  if (fabs(D) < EPS)
    return {1, ans1, 0};
  Real ans2 = C / (A * ans1);
  if (ans1 > ans1)
    swap(ans1, ans2);
  return {2, ans1, ans2};
}