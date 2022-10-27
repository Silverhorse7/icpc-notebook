	bImpartial Games : 
-same set of moves at any time allowed for both players
-Nim Game : for any player , pick whatever items
Partisan Games : 
- The moves for all the players are not the same.
- Tricky and hard to analyze
- chess, each player moves only his own pieces
- TicTacToe : player 1 plays X only while 2 plays O only
- Typicall backtracking/dp/minimax coding
- usually search techniques,dynamic programming

for every game, evaluate 3 things :
-Winning position
-Losing  position
-Terminal position

--Remember : Game tree , whatever made u lose , is defintely win, terminal is lose , if u have no loses, is lose.

-first things to try : 
-always try to solve for reduced cases ( like n= 2 ) , a=b , a>b,a<b,etc.
-grundy theorem
-piles
-independent
-mex
-Strategies : 
--Move duplication strategy : duplicate everything ur oppenent does
--Move cancellation strategy : make ur moves so that u cancel ur oppenent's moves.,ex : poker nim

Nim Games : 
standard : winner takes last stone , no other rules 
solution : xor!=0
Misere Nim : last one to move loses
solution : standard solution , but if all piles <=1 , then if xor==0 ,first wins
Moore's nim-k : remove stones from any k piles
solution : for every bit , check if cnt[bit]%(k+1)
standard with skips A,B :
solution : if(A==B) : standard solution else, output bigger A,B name

Grundy :
if losing terminal position : 0
else
mex( nimber(move1),nimber(move2),nimber(move3),...)
ex : 
nim for 1 pile, take 1,2,3
grundy(0) = 0 ->terminal case
grundy(1) = mex(grundy(0)
grundy(2)= mex(grundy(0),grundy(1))
grundy(3) = mex(grundy(0),grundy(1),grundy(2)}
grundy(X) =mex(grundy(X-1),grundy(X-2),grundy(X-3) )
