#include <iostream>
#include <cstdint>
#include <vector>

#include <random>
#include <limits>

typedef std::vector<std::uint8_t> DType;

DType MakeVector01(std::size_t N, unsigned int S = 0) {
	
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> UI(0, 255);
	
	DType R;


	for (std::size_t i = 0; i < N; i++) {
		R.push_back(UI(mt));
	}

	return R;
}

DType ZeroOne_Enc(const DType& N) {
	DType R;

	for (auto& o:N) {
		for (std::size_t i = 0; i < std::numeric_limits<DType::value_type>::digits;i++) {
			auto X = (o & (1 << i))>0? 1:0 ;
			R.push_back(X);
		}
	}

	return R;
}
DType ZeroOne_Dec(const DType& N) {
	DType R;
	std::uint8_t X = 0;;
	for (std::size_t i = 0; i < N.size(); i++) {

		X |= N[i] << (i % (std::numeric_limits<DType::value_type>::digits));

		if ((i % (std::numeric_limits<DType::value_type>::digits)) == std::numeric_limits<DType::value_type>::digits-1) {
			R.push_back(X);
			X = 0;
		}
	}

	return R;
}

bool Show(const DType& In) {
	for (auto& o : In) {
		std::cout << (int)o<<",";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return true;
}

int main() {

	auto V = MakeVector01(128);

	Show(V);

	DType E = ZeroOne_Enc(V);

	Show(E);
	DType D = ZeroOne_Dec(E);
	
	Show(D);

	if (V == D) {
		std::cout << "Good." << std::endl;
	}
	else {
		std::cout << "Bad." << std::endl;
	}


	return 0;
	

}