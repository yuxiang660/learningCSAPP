all: target_diff

target:
	g++ -c main.cpp -o main.o -D_GLIBCXX_USE_CXX11_ABI=1
	nm main.o | cut -c 20- > main.symbols

target_old:
	g++ -c main.cpp -o main_old.o -D_GLIBCXX_USE_CXX11_ABI=0
	nm main_old.o | cut -c 20- >main_old.symbols

target_diff: target target_old
	diff --suppress-common-lines main.symbols main_old.symbols || true

clean:
	@rm -rf *.o *.symbols