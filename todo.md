rule
- one global variable permitted: errnoだと思う
- write, ft_printf
- void (*signal(int sig, void (*func)(int)))(int): シグナルを処理する方法を設定する
- int sigemptyset(sigset_t *set): シグナルセットsetを操作, setを空に初期化（include <signal.h>）, 戻り値：0
- int sigaddset(sifset_t *set, int signo): setに指定のシグナルsignoを追加, 戻り値：0
- int sigaction(int sig, const struct sigaction * restrict act, struct sigaction * restrict oact):
- int kill(pit_t pid, int sig): プロセスpidにシグナルsigを送信, sig=0の場合、エラーチェックを実行しシグナルは送信しない。sigをsigactionで規定されたシグナルの一つにすることも可能。return: the value 0 if successful; otherwise the value -1 is returned and the global variable errno is set to indicate the error.
  kill() システムコールは次の場合に処理に失敗し、シグナルは送信されません
[EINVAL]
 	sig 引数が有効なシグナル番号ではありません。
[ESRCH]
 	pid で指定されたプロセスに対応するプロセスが検出できません。
[ESRCH]
 	プロセス ID は 0 として与えられたものの、 送信プロセスにプロセスグループがありません。
[EPERM]
 	送信プロセスはスーパユーザではなく、その実効ユーザ ID が受信プロセスの 実効ユーザ ID と一致しません。 プロセスグループにシグナルを送信するとき、グループのメンバの いずれかにシグナルを送信することができない場合、このエラーが返されます。
- pid_t getpid(void): 親または呼び出しプロセスのプロセスIDを返す
- malloc, free
- int pause(void): 次のシグナルを待つ。次のシグナル（シグナル捕獲関数）から返った場合に-1を返し、errnoにEINTRが設定される(include <unistd.h>)
- unsigned int sleep(unsigned int seconds): 指定の秒数の間だけ休止する。要求された時間が過ぎた場合はゼロを返す。呼び出しがシグナルハンドラーに割り込まれた場合は休止の残り時間を返す。
- unsigned int usleep(unsigned int seconds): マイクロ秒単位で実行を延期する。若干システムの動作状況などによって停止時間は設定した値よりも少し伸ばされる可能性あり。成功すると0を返し、エラーの場合-1が返されerrnoにエラーの原因を示す値が設定される
- exit: プログラムを実行した側にプログラムの成功や失敗を伝える一つの手段。引数は終了ステータス（負の値は扱えないため0~255で返す）。exit(0)は正常終了、exit(1以上)は異常終了。（include <stdlib.h>。因みにexit_successなどの値はsysexits.hに定義されている）
- シグナルセット：シグナルグループを1つのプロセスにより経過の記録を撮るためのデータオブジェクト
	
   in signal.h
	9 #define _NSIG       64
   10 #define _NSIG_BPW   32
   11 #define _NSIG_WORDS (_NSIG / _NSIG_BPW) ←なんで２？
   15 typedef struct {
   16     unsigned long sig[_NSIG_WORDS];
   17 } sigset_t; ←なんで構造体なのに要素1つだけ？
   → sigset_tはunsigned long sig[2]を要素に持つ構造体


mandatory part
- create a communication program in the form of a client and server
- the server must be launched first, and then display its PID
- the client takes as params: the server PID, the string that should be sent
- the client must communicate the string passed as a param to the server, and once the string has been recieved, the server must display it
- communication between your programs should only be done using **unix signals**
- the server must be able to display the string pretty quickly, which means if 1 seconds for 100 characters..it's colossal
- the server should be able to recieve strings from several clients in a row, without restart
- you can only use the two signals: sigusr1 and sigusr2

attension: linux system do not queue signals when you already have pending signal of this type! bonus time?

bonus
- the server confirms every signal received by sending a signal to the client
- support unicode characters

server
1. Create socket
2. Bind to address and port
3. Put in listening mode
4. Accept connections and process there after

11/5F
- [ ] todo作成

TODO for 5 days
今分からないこと
- signal使って各ハンドラーに行く流れ...ハンドラーは関数として自分で実装すべきところなのか、それともsignal.hに書いてあるってことで直ぐ呼び出し可能か
- ハンドラーをパラメータとするとき、パラメータはどういう形になるか
- 初期化は毎回通るのか、それとも通信中に一回だけ通るべきか
- sigactionがどういう役割か分からない
- signalとpid、どっちが先に処理されるべきなのか、または同時なのか
- 全体像が分からない、serverとclientの役割分担が不明
- serverを起動する方法が分からない、exeファイルで実行する感じでいいのか？
調べる順番（大きい概念　→　小さい概念）
- serverとclientの役割分担
- serverの起動方法
- signalとpidの実装順番
- signal、pidのそれぞれの実装
  - signalの流れ、全体像
  - pidの流れ、全体像

- [ ] server
  - [ ] signalで各ハンドラーの関数に飛べるようにする
    - [ ] sigemptyset: 初期化
    - [ ] sigaddset: setに指定のsignoを追加
    - [ ] sigaction: 
- [ ] 
- [ ] 