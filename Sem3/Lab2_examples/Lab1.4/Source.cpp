#include <iostream>
using namespace std;

template<int ... Idxs> struct IndexesTuple
{ };

template<int Num, typename Tp = IndexesTuple<>>
struct IndexTupleBuilder;

template<int Num, int ... Idxs>
struct IndexTupleBuilder<Num, IndexesTuple<Idxs ...>> : IndexTupleBuilder<Num - 1, IndexesTuple<Idxs ..., sizeof ... (Idxs)>>
{ };

template<int ... Idxs>
struct IndexTupleBuilder<0, IndexesTuple<Idxs ...>>
{
	typedef IndexesTuple<Idxs...> Indexes;
};

template<int idx, typename T>
struct DataHolder
{
	DataHolder(T const& data) : m_data(data) { }
	T m_data;
};

template<typename IdxsTuple, typename ... F> struct ComposerBase;

template<int ... Idxs, typename ... F>
struct ComposerBase<IndexesTuple<Idxs...>, F ...> : public DataHolder<Idxs, F>...
{
	ComposerBase(F ... fs) : DataHolder<Idxs, F>(fs)... { }
};

template<typename Op, typename ... F>
struct Composer : public ComposerBase<typename IndexTupleBuilder<sizeof...(F)>::Indexes, F...>
{
	Op m_op;
public:
	typedef ComposerBase<typename IndexTupleBuilder<sizeof...(F)>::Indexes, F...> Base;
	typedef decltype(m_op((*(F*)NULL)(0)...)) result_t;

	Composer(Op op, F const &... fs) : m_op(op), Base(fs...) { }

	result_t operator()(int x) const
	{
		return MakeCall(x, typename IndexTupleBuilder<sizeof...(F)>::Indexes());
	}
private:

	template<int ... Idxs>
	result_t MakeCall(int x, IndexesTuple<Idxs...> const&) const
	{
		return m_op(DataHolder<Idxs, F>::m_data(x)...);
	}
};

template<typename Op, typename ... F>
Composer<Op, F ...> Compose(Op op, F ... fs)
{
	return Composer<Op, F...>(op, fs ...);
}


int opr3(int a, int b, int c)
{
	return (a + b)*(a + b)*c;
}

double fn1(double a)
{
	return a * 2;
}

int fn2(int a)
{
	return a * 3;
}

int fn3(int a)
{
	return a * 4;
}

int main()
{
	/////////////////////////////////TESTS/////////////////////////////////////
	//auto h = Compose(opr3, fn1, fn2, fn3);
	auto h = Compose([](int x, int y, int z) { return (x + y)*(x + y)*z; },
		[](int x) {return x * 2; },
		[](int x) {return x * 3; },
		[](int x) {return x * 4; });
	cout << "h=" << h(5) << endl;
	//-------------------------------------------------------------------

	system("pause");
}