# MANDELBROT

Lightweight Mandelbrot set viewer.

# USAGE

## I. PRODUCING THE MATRIX

```
// params
std::pair<double, double> p = {0, 0};
double R = 2.0;
double inc = R / 200.0;
int max_iter = (1<<16);

// runner
auto res = plotCentered(p.first, p.second, R, R, inc, max_iter);
auto values = histo_values(res, max_iter, BANDS);
cout << "[" << BANDS << "," << values.size() << "," << values[0].size() << "]" << endl; // Yes this is needed -- it specifies the dimensions of the image and the number of colors to use.
cout << output_histo(values);
```

Copy `stdout` to `mandelbrot.out` to save your file.

`main.cpp` basically does all of this for you as a simple example:

```
g++ main.cpp -o main -O3
./main > mandelbrot.out
```

## II. RENDERING

Run `render.py` to produce an image. Be sure to `pip install pillow` first and make sure to set the `INPUT` value to the matrix file path (in this example `mandelbrot.out`).

---

![Example!](801px.PNG?raw=true)