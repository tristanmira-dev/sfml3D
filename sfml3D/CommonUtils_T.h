template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vertices) {
		for (T const& val : vertices) {
			os << val << "\n";
		}
		return os;
}