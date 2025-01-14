## 3383. 球的半径

float和double的占位符：printf中都是 `%f`，scanf中是 `%f / %lf`

$\pi$ 的写法： `acos(-1)`

```
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = acos(-1);

int main() {
    double x0, y0, z0;
    double x1, y1, z1;
  
    cin >> x0 >> y0 >> z0 >> x1 >> y1 >> z1;
    double radius = sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1) + (z0-z1)*(z0-z1));
    double volume = 4.0 / 3.0 * PI * radius * radius * radius;
  
    printf("%.3f %.3f\n", radius, volume);
  
    return 0;
}
```
