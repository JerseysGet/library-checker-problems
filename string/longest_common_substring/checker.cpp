// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/wcmp.cpp

// The MIT License (MIT)

// Copyright (c) 2015 Mike Mirzayanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  setName("compare sequences of tokens");
  registerTestlibCmd(argc, argv);

  string s = inf.readToken();
  string t = inf.readToken();
  int n = s.size(), m = t.size();

  int a1 = ans.readInt(0, n);
  int b1 = ans.readInt(0, n);
  int c1 = ans.readInt(0, m);
  int d1 = ans.readInt(0, m);

  int a2 = ouf.readInt(0, n);
  int b2 = ouf.readInt(0, n);
  int c2 = ouf.readInt(0, m);
  int d2 = ouf.readInt(0, m);

  auto check = [&](int a, int b, int c, int d) -> int {
    // ng: -1
    // ok: length
    if (!(0 <= a && a <= b && b <= n)) return -1;
    if (!(0 <= c && c <= d && d <= m)) return -1;
    if (a == b && a != 0) return -1;
    if (c == d && c != 0) return -1;
    if (b - a != d - c) return -1;
    int n = b - a;
    for (int i = 0; i < n; ++i) {
      if (s[a + i] != t[c + i]) return -1;
    }
    return b - a;
  };

  int x1 = check(a1, b1, c1, d1);
  int x2 = check(a2, b2, c2, d2);

  if (x1 == -1 || x1 < x2) {
    quitf(_fail, "participant has the better answer");
  }
  if (x2 == -1) { quitf(_wa, "not common substrings"); }
  if (x2 < x1) { quitf(_wa, "not longest"); }
  quitf(_ok, "ok");
}
