#include <iostream>
#include <list>

// ineed type holder type variable.

//struct Any {
//	types T = void;
//	T value = T();
//};

template<class T>
class DataIO {
public:

	DataIO(const std::initializer_list<T>& L) {
		Data.insert(Data.begin(),L.begin(), L.end());
	}
	void Craft(std::size_t N, auto mk) {//double craft.
		for (std::size_t i = 0; i < N; i++) {//1
			Data.push_back(mk(Data));
		}
	}
	void Push(const T& in) {
		Data.push_back(in);
	}
	auto Gets(auto lf) {
		std::list<auto> l;
		for (auto& o: Data) {
			if (lf(o)) { l.push_back(&o); }
		}
		return l;
	}

	template<class Y>
	void Set(auto lf, const Y& D) {
		for (auto& o : Data) {
			if (lf(o)) { o = D; }
		}
	}
	template<class Y>
	void Set(auto lf, auto ch, const Y& D) {
		for (auto& o : Data) {
			if (lf(o)) { ch(o, D); }
		}
	}

	void Auto(auto F) {
		for (auto& o : Data) {
			F(o);
		}
	}

	void Lambad(auto F) {
		for (auto& o: Data) {
			F(o);
		}
	}

	void IF(auto IF, auto F) {
		for (auto& o : Data) {
			if (IF(o)) { F(o); }
		}
	}

	auto One(std::size_t Idx, auto lf) {
		auto it = Data.begin();
		if (Idx >= Data.size()) { return {}; }
		for (size_t i = 0; i < Idx; i++) {
			it++;
		}

		return lf(it);
	}

	auto One(auto F) {
		return F(this, Data);
	}

	bool Erase(auto lf) {
		auto it = Data.begin();
		for (size_t i = 0; i < Data.size(); i++) {
			if (lf(it)) { Data.erase(it); it--; }
		}
		return true;
	}

	auto Class(auto Con, auto Flow, auto Des) {
		if (!Con(this)) { return {}; }
		if (!Flow(this)) { return {}; }
		return Des(this);
	}

	auto Flow(auto Beg, auto Centar, auto End) {
		if (!Beg(this)) { return {}; }
		if (!Centar(this)) { return{}; }
		return End(this);
	}

	std::size_t Size() {
		return Data.size();
	}

	auto Begin() {
		return Data.begin();
	}
	auto End() {
		return Data.end();
	}

protected:
	std::list<T> Data;
};

#include <string>

int main() {
	DataIO<std::string> D = {"1","2","3"};

	D.Auto([](auto o) {std::cout << o << std::endl; });
	D.Craft(16, [](auto l) {std::string s; for (auto& o : l) { s += o; s += "x"; }; return s; });
	D.Auto([](auto o) {std::cout << o << std::endl; });
	std::size_t X = 0;
	D.Auto([&](auto& o) { X += o.size(); });

	std::cout << X << std::endl;

	return 0;
}