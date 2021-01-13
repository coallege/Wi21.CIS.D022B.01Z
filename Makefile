%.exe: %.cxx
	clang++ -Wall $< -o $@

run~%: %.exe
	$<
