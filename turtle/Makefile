CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror -lc
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: parse_s interp_s extension_s

parse_s: Parse/parse.h Parse/parse.c  Parse/test_Parse.c Parse/test_Parse.h
	$(CC) Parse/parse.c  Parse/test_Parse.c -o parse_s -I./Parse $(SANITIZE) -lm

interp_s: Interp/interp.h Interp/interp.c Interp/test_Interp.h Interp/test_Interp.c neillsimplescreen.c neillsimplescreen.h STACK/Linked/stack.c STACK/stack.h STACK/general.c STACK/general.h
	$(CC) STACK/Linked/stack.c STACK/general.c neillsimplescreen.c Interp/interp.c Interp/test_Interp.c -o interp_s -I./Interp $(SANITIZE) -lm

### An example : you may wish to adapt this slightly
extension_s: Extension/extension.h Extension/extension.c neillsimplescreen.c neillsimplescreen.h STACK/Linked/stack.c STACK/stack.h STACK/general.c STACK/general.h
	$(CC) STACK/Linked/stack.c STACK/general.c neillsimplescreen.c Extension/extension.c -o extension_s -I./Extension $(SANITIZE) -lm


run: all
	./parse_s TTLs/empty.ttl
	./parse_s TTLs/forward.ttl
	./parse_s TTLs/ok_parse_fail_interp.ttl
	./parse_s TTLs/set1.ttl
	./parse_s TTLs/donothing.ttl
	./parse_s TTLs/set2.ttl
	./parse_s TTLs/turn.ttl
	./parse_s TTLs/spiral.ttl
	./parse_s TTLs/octagon1.ttl
	./parse_s TTLs/octagon2.ttl
	./parse_s TTLs/tunnel.ttl
	./parse_s TTLs/labyrinth.ttl
	./parse_s TTLs/hypno.ttl
	./parse_s TTLs/5x5.ttl
	./parse_s TTLs/downarrow.ttl
	./interp_s TTLs/empty.ttl out_empty.txt
	./interp_s TTLs/forward.ttl out_forward.txt
	./interp_s TTLs/set1.ttl out_set1.txt
	./interp_s TTLs/donothing.ttl out_donothing.txt
	./interp_s TTLs/fail_parse_ok_interp.ttl out_fail_parse_ok_interp.txt
	./interp_s TTLs/set2.ttl out_set2.txt
	./interp_s TTLs/turn.ttl out_turn.txt
	./interp_s TTLs/spiral.ttl out_spiral.txt
	./interp_s TTLs/octagon1.ttl out_octagon1.txt
	./interp_s TTLs/octagon2.ttl out_octagon2.txt
	./interp_s TTLs/tunnel.ttl out_tunnel.txt
	./interp_s TTLs/labyrinth.ttl out_labyrinth.txt
	./interp_s TTLs/hypno.ttl out_hypno.txt
	./interp_s TTLs/5x5.ttl out_5x5.txt
	./interp_s TTLs/downarrow.ttl out_downarrow.txt
	./interp_s TTLs/empty.ttl out_empty.ps
	./interp_s TTLs/forward.ttl out_forward.ps
	./interp_s TTLs/set1.ttl out_set1.ps
	./interp_s TTLs/donothing.ttl out_donothing.ps
	./interp_s TTLs/fail_parse_ok_interp.ttl out_fail_parse_ok_interp.ps
	./interp_s TTLs/set2.ttl out_set2.ps
	./interp_s TTLs/turn.ttl out_turn.ps
	./interp_s TTLs/spiral.ttl out_spiral.ps
	./interp_s TTLs/octagon1.ttl out_octagon1.ps
	./interp_s TTLs/octagon2.ttl out_octagon2.ps
	./interp_s TTLs/tunnel.ttl out_tunnel.ps
	./interp_s TTLs/labyrinth.ttl out_labyrinth.ps
	./interp_s TTLs/hypno.ttl out_hypno.ps
	./interp_s TTLs/5x5.ttl out_5x5.ps
	./interp_s TTLs/downarrow.ttl out_downarrow.ps
### =============test===============
	./parse_s TTLs/simpleFWD.ttl
	./parse_s TTLs/simpleFWDRGT.ttl
	./parse_s TTLs/simpleFWDRGTCOL.ttl
	./parse_s TTLs/simpleSET.ttl
	./parse_s TTLs/simpleLoopNum.ttl
	./parse_s TTLs/simpleLoopVar.ttl
	./interp_s TTLs/simpleFWD.ttl out_testFWD.txt
	./interp_s TTLs/simpleFWDRGT.ttl out_testFWDRGT.txt
	./interp_s TTLs/simpleFWDRGTCOL.ttl out_testFWDRGTCOL.txt
	./interp_s TTLs/simpleSET.ttl out_testSET.txt
	./interp_s TTLs/simpleLoopNum.ttl out_testLNUM.txt
	./interp_s TTLs/simpleLoopVar.ttl out_testLVAR.txt
### =============extension===============
	./extension_s TTLs/ex_test1.ttl out_extest1.txt
	./extension_s TTLs/ex_test2.ttl out_extest2.txt
	./extension_s TTLs/ex_test3.ttl out_extest3.txt
	./extension_s TTLs/ex_test4.ttl out_extest4.txt

clean:
	rm -f parse_s interp_s extension_s out_*.txt out_*.ps out_*.pdf
