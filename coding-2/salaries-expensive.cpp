#include <iostream>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

enum mode {
	inc,
	dec
};

struct pair {
	pair(int first, int second)
	{
		this->first = first;
		this->second = second;
	}

	pair()
	{
		this->first = 0;
		this->second = 0;
	}

	int first, second;
};

template <typename T>
struct arr {
	arr()
	{
		this->_arr = nullptr;
		this->size = 0;
	}

	arr(int size)
	{
		this->_arr = new T[size];
		this->size = size;
	}

	~arr()
	{
		delete[] _arr;
	}

	T &operator[](int i)
	{
		return _arr[i];
	}

	arr &operator=(const arr &other)
	{
		delete[] _arr;
		size = other.size;
		_arr = new T[size];
		for (int i = 0; i < size; i++) {
			_arr[i] = other._arr[i];
		}

		return *this;
	}

	T *_arr;
	int size;
};

arr<int> p;
arr<int> revK;
arr<pair> maxf;
arr<pair> maxb;
arr<pair> chf;
arr<pair> chb;

int bin(arr<int> &a, int l, int r, int x, mode mod)
{
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (mod == inc ? a[m] >= x : a[m] <= x) {
			r = m;
		}
		else {
			l = m;
		}
	}

	return r;
}

void longest(arr<int> &a, mode mod)
{
	arr<pair> &maxL = (mod == inc) ? maxf : maxb;
	arr<pair> &ch = (mod == inc) ? chf : chb;

	arr<int> tail = arr<int>(a.size);
	for (int i = 0; i < a.size; i++) {
		tail[i] = 0;
	}

	/* i = 0 */
	int length = 1;
	maxL[0].first = 1;
	maxL[0].second = a[0];
	ch[0].first = 1;
	ch[0].second = a[0];
	tail[0] = a[0];

	for (int i = 1; i < a.size; i++) {
		/* case 1: element is smaller than everything */
		if (mod == inc ? a[i] < tail[0] : a[i] > tail[0]) {
			maxL[i].first = length;
			maxL[i].second = (length == 1 ? a[i] : tail[length - 1]);
			ch[i].first = 1;
			ch[i].second = a[i];
			tail[0] = a[i];
		}

		/* case 2: element is bigger than everything */
		else if (mod == inc ? a[i] > tail[length - 1] : a[i] < tail[length - 1]) {
			maxL[i].first = length + 1;
			maxL[i].second = a[i];
			ch[i].first = length + 1;
			ch[i].second = a[i];
			tail[length] = a[i];
			length++;
		}

		/* case 3: element is in between */
		else {
			int idx = bin(tail, -1, length - 1, a[i], mod);
			tail[idx] = a[i];
			maxL[i].first = length;
			maxL[i].second = tail[length - 1];
			ch[i].first = idx + 1;
			ch[i].second = a[i];
		}
	}
}

int main()
{

	int N, K;

	std::cin >> N >> K;

	p = arr<int>(N);
	revK = arr<int>(N);

	maxf = arr<pair>(N);
	maxb = arr<pair>(N);

	chf = arr<pair>(N);
	chb = arr<pair>(N);

	for (int i = 0; i < N; i++) {
		std::cin >> p[i];
	}
	for (int i = 0; i < N; i++) {
		revK[i] = p[(N - 1) - i] + K;
	}

	longest(p, inc);
	longest(revK, dec);

	int answer = maxf[maxf.size - 1].first;

	for (int i1 = 0, i2 = N - 2; i1 < N - 1; i1++, i2--) {
		if (maxf[i1].second < maxb[i2].second) {
			answer = max(answer, maxf[i1].first + maxb[i2].first);
		}
	}

	for (int i1 = 0, i2 = N - 2; i1 < N - 1; i1++, i2--) {
		if (chf[i1].second < chb[i2].second) {
			answer = max(answer, chf[i1].first + chb[i2].first);
		}
	}

	answer = min(answer, N);

	std::cout << answer << std::endl;

	while (1) {
	}
}
