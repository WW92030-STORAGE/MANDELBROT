#include <bits/stdc++.h>
using namespace std;

#include "mandelbrot.h"

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	pair<frac, frac> p = {-0.724432149, 0.244623719};
	p = {-0.7893745992714669, 0.1630892526775267};
	p = {-0.74453986035590838012, 0.12172377389442482241}; // https://www.mrob.com/pub/muency/seahorsevalley.html
	frac R = 1.0 / (1<<16);
	frac inc = R / 800;
	int max_iter = 1<<16;
	int BANDS = 16;
	auto res = plotCentered(p.first, p.second, R, R, inc, max_iter);
	auto values = histo_values(res, max_iter, BANDS);
	cout << "[" << BANDS << "," << values.size() << "," << values[0].size() << "]" << endl;
	cout << output_histo(values);


	std::cout << "End\n";



	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	int64_t count = duration.count();
    std::cout << "Time taken: " << count << " us" << std::endl;
	std::cout << "Time taken: " << count * 0.001 << " ms" << std::endl;
	std::cout << "Time taken: " << count * 0.000001 << " s" << std::endl;
	return 0;
}