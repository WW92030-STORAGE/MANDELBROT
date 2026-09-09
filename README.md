# MANDELBROT

Lightweight Mandelbrot set viewer.

# USAGE

```
// params
std::pair<double, double> p = {0, 0};
double R = 2.0;
double inc = R / 200.0;
int max_iter = (1<<16);

// runner
auto res = plotCentered(p.first, p.second, R, R, inc, max_iter);
auto values = histo_values(res, max_iter, BANDS);
cout << "[" << BANDS << "," << values.size() << "," << values[0].size() << "]" << endl;
cout << output_histo(values);
```

Copy `stdout` to `mandelbrot.out` and run `render.py` to produce an image. Be sure to `pip install pillow` first.