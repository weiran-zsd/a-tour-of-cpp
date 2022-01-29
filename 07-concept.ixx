import <concepts>;
export module _07_concept;

template<typename Seq, typename Num>
//requires Sequence<Seq> && Number<Num> && Arithmetic<Value_type<Seq> Num>
Num sum(Seq s, Num v) {
	for (const auto& x : s) {
		v += x;
	}
	return v;
}


//template<Forward_iterator lter>
//void advance(lter p, int n) {
//	for (--n)++p;
//}

// requires ���ʽ

// 7.2.4 ����Ķ���
//template<typename T>
//concept Equality_comparable =
//	requires(T a, T b) {
//		{a == b} -> bool;
//		{a != b} -> bool;
//};

// 7.4.2 ���ʽ�۵�
template<typename... T>
int sum(T... v) {
	return (v + ... + 0);
}