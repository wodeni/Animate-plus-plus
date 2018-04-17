template<typename Container>
void print(const Container& cont) {
   for (auto const& x : cont) {
      std::cout << "\"" << x  << "\"" << " ";
   }
   std::cout << '\n';
}
