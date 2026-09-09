#include <utility>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>

typedef double frac;
typedef std::pair<frac, frac> point;

namespace MANDELBROT {
	constexpr char SYMBOLS[] = {
			' ', '.', '_', '-', 
			':', '~', '=', '|', 
			'/', '+', '*', 'o', 
			'O', '8', '%', '#'
		};

	constexpr int N_SYM = 16;
	constexpr char INTERIOR = '@';

	std::string test_symbols(int r = 40, int c = 5) {
		std::string res = "";
		for (int k = 0; k < N_SYM; k++) {
			for (int i = 0; i < c; i++) {
				for (int j = 0; j < r; j++) {
					res.push_back(SYMBOLS[k]);
				}
				res.push_back('\n');
			}
		}
		return res;
	}
};

// has the point escaped?
inline bool escaped_heuristic(point z, point csq) {
	return csq.first + csq.second >= 4;
}

// do we know that the point is inside?
inline bool early_interior(point p) {
	// main cardoid chdck
	frac ysq = p.second * p.second;
	frac offset_x = p.first - 0.25;
	frac q = offset_x * offset_x + ysq;
	if (q * (q + offset_x) <= 0.25 * ysq) return true;
	// period 2 bulb
	offset_x = p.first + 1;
	if (offset_x * offset_x + ysq <= 1.0 / 16.0) return true;

	return false;
}

int escapetime(point p, int max_iter = 1024, bool EIC = false) {
	if (EIC && early_interior(p)) return -1;
	point z = {0, 0};
	point csq = {0, 0};
	for (int it = 0; it < max_iter; it++) {
		// heuristic to count as escaped
		if (escaped_heuristic(z, csq)) return it; 
		csq.first = z.first * z.first;
		csq.second = z.second * z.second;
		z.second = (z.first + z.first) * z.second + p.second;
		z.first = csq.first - csq.second + p.first;
	}
	return -1;
}

std::vector<std::vector<int>> plotCentered(frac sx = 0, frac sy = 0, frac rx = 2, frac ry = 2, frac inc = 0.01, int max_iter = 1024, bool EIC = false) {
	int nx = rx / inc;
	int ny = ry / inc;
	int szx = nx * 2 + 1;
	int szy = ny * 2 + 1;

	std::vector<std::vector<int>> res(szx, std::vector<int>(szy, -1));

	for (int xi = 0; xi < szx; xi++) {
		for (int yi = 0; yi < szy; yi++) {
			frac x = sx + inc * (xi - nx);
			frac y = sy + inc * (yi - ny);
			res[xi][yi] = escapetime({x, y}, max_iter, EIC);
		}
	}
	return res;
}

std::vector<std::vector<int>> histo_values(std::vector<std::vector<int>>& v, int64_t max_iter = 1024, int BANDS = 16) {
	if (BANDS > MANDELBROT::N_SYM) BANDS = MANDELBROT::N_SYM;
	int scaleFactor = (MANDELBROT::N_SYM / BANDS);
	std::vector<int64_t> histo(max_iter, 0); // histogram and prefix sum
	int x = v.size();
	int y = v[0].size();
	for (int i = 1; i < x; i++) y = (v[i].size() > y) ? y : v[i].size();
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			if (v[i][j] < 0) continue;
			histo[v[i][j] > max_iter ? max_iter : v[i][j]]++;
		}
	}

	std::vector<std::vector<int>> res(x, std::vector<int>(y, 0));

	int64_t histo_sum = 0;
	for (auto i : histo) histo_sum += i;
	for (int i = 1; i < max_iter; i++) histo[i] += histo[i - 1];
	frac hsd = histo_sum;

	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			if (v[i][j] < 0) res[i][j] = -1;
			else {
				frac val = (frac)(std::min(histo_sum, histo[v[i][j]])) / hsd;
				// cout << i << " " << j << " " << v[i][j] << " " << histo.size() << " " << histo[v[i][j]] << " " << hsd << " = " << val << "\n";
				res[i][j] = ((int)(val * BANDS));
				res[i][j] *= scaleFactor;
			}
		}
	}

	return res;
}

// takes in the output of histo_values
std::string disp_histo(std::vector<std::vector<int>>& v) {
	std::string res = "";
	int x = v.size();
	int y = v[0].size();
	for (int i = 1; i < x; i++) y = (v[i].size() > y ? y : v[i].size());
	for (int j = y - 1; j >= 0; j--) {
		for (int i = 0; i < x; i++) {
			if (v[i][j] < 0) res.push_back(MANDELBROT::INTERIOR);
			else res.push_back(MANDELBROT::SYMBOLS[std::min(v[i][j], MANDELBROT::N_SYM - 1)]);
		} 
		res.push_back('\n');
	}
	return res;
}

std::string output_histo(std::vector<std::vector<int>>& v) {
	std::string res = "";
	int x = v.size();
	int y = v[0].size();
	for (int i = 1; i < x; i++) y = (v[i].size() > y ? y : v[i].size());
	for (int j = y - 1; j >= 0; j--) {
		for (int i = 0; i < x; i++) {
			res += std::to_string(v[i][j]);
			res.push_back(',');
		} 
		res.push_back('\n');
	}
	return res;
}
