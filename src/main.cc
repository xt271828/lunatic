
#include "scriptengine.h"

using namespace lunatic;
template<typename T>
void timing(T f) {
	f();
}



std::string get() {
	std::string tmp;
	std::getline(std::cin, tmp);
	return tmp;
}

void Interactive() {
	ScriptEngine engine;
	std::string source;
	println("lunatic 0.1  (build at {} {})", __DATE__,__TIME__);
	while (!feof(stdin)) {
		std::cout << "< ";
		std::getline(std::cin, source);
		source.append(";");
		Error err;
		auto tryExec = [&]() {
			err = engine.execString(source, "stdin");
		};
		auto exec = [&]() {
			err = engine.execString(source, "stdin");
			if (err.code != ErrorCode::None) {
				std::cerr << err.message << std::endl;
			}
		};
		tryExec();
		
		if (err.code != ErrorCode::None) {
			// enter multi-line loop
			source.pop_back();

			bool empty = false;
			while (true) {
				if (err.code == ErrorCode::RuntimeError||err.code == ErrorCode::CompilerError) {
					std::cerr << err.message << std::endl;
					break;
				}
				std::cout << "...";
				auto s = get();
				source.append("\n").append(s);
				//std::cout << source << std::endl;
				if (s.empty()) {
					if (empty) {
						exec();
						break;
					}
					empty = true;
				}
				else {
					empty = false;
				}
				
				tryExec();
				if (err.code == ErrorCode::None)
					break;
				
			}
		}
		source.clear();
	}
}

int main(int argc, char** argv) {
	ScriptEngine engine;

	if (argc == 1) {
		Interactive();
	}
	else {
		for (int i = 1; i < argc; i++) {
			Error err;
			timing([&]() {
				err = engine.execFile(argv[i]);
			});
			if (err.code != ErrorCode::None) {
				std::cerr << err.message << std::endl;
			}
		}
	}
}