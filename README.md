# 🔃 push_swap — 2 本のスタックを少ない操作回数で整列させる

![language](https://img.shields.io/badge/language-C-blue.svg)
![norm](https://img.shields.io/badge/42-norminette-success.svg)
![flags](https://img.shields.io/badge/build-Wall%20Wextra%20Werror-brightgreen.svg)
![platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey.svg)

> **TL;DR (EN):** A [42](https://42tokyo.jp/) project that sorts integers using only two
> stacks and eleven allowed operations, printing the operation list to stdout.
> Stacks are fixed-size arrays with a sentinel element, so the whole program does exactly
> two `malloc` calls and never allocates again while sorting. The sort is a greedy
> insertion: push everything to stack B, then repeatedly pick the element whose round trip
> back to A costs the fewest operations, counting `rr`/`rrr` fusions in the cost model.
> 798 lines across 8 files (33 functions), `-Wall -Wextra -Werror`, norminette-clean.

本プロジェクトは 42 の課題 **push_swap** の実装です。整数列を **2 本のスタックと 11 種類の操作だけ**で
昇順に並べ替え、その操作列を標準出力に印字します。プログラム自体はソートを実行するのではなく
「ソートの手順書」を出力し、正しさは別途 checker で操作列を再生して検証する課題構成になっています。

## 概要

- **操作**: `sa` `sb` `ss` / `pa` `pb` / `ra` `rb` `rr` / `rra` `rrb` `rrr` の 11 種類。
- **入力**: 複数引数（`./push_swap 3 1 5 2 4`）と 1 引数のクォート文字列（`./push_swap "3 1 5 2 4"`）の両方。
  後者は空白・タブ・改行で分割します。
- **出力**: スタック A が昇順・B が空になる操作列。整列済みなら何も出力しません。
- **エラー**: 数字以外の文字・重複・不正な形式は `Error` を出力して終了します。

---

## 実装のポイント

### 連結リストではなく固定長配列

スタックを `t_elem` の配列で表現しました。要素は 3 フィールドだけです。

```c
typedef struct s_elem
{
	int		num;     /* 値 */
	int		filled;  /* このスロットが現在有効か */
	int		index;   /* 自身の添字（末尾の番兵は -1） */
}	t_elem;
```

起動時に A 用・B 用の 2 本を `malloc` するだけで、以降は再確保も個別解放もしません。
**動的確保はプログラム全体で 2 回**、解放は `ft_free` の 1 箇所に集約されており、
ソートのメインループ内で確保が起きないため確保失敗をソート経路で考慮する必要がありません。

末尾に `index == -1` の番兵を置き、長さを持ち回りません。各スタックは配列の後方の連続領域を占め、
「上端」は `filled == 1` となる最小添字です。`index` を要素自身に持たせたことで、
`get_min_stack` / `get_max_stack` / `get_min_above_tresh` が `t_elem` を返しても呼び出し側が位置を復元でき、
探索結果をそのままコスト計算へ渡せます。

代償として、回転操作 `shift_up` / `shift_down` はヘッドポインタを進めるのではなく配列内の `num` を
1 つずつ物理的にずらす実装であり、**回転 1 回が O(n)** です。

### 11 命令を 5 関数で実装する

すべての操作を「出力文字列を引数で受け取る」形に統一しました。

```c
shift_up(stack_a, "ra\n");   /* ra */
shift_up(stack_b, "rb\n");   /* rb — 同じ関数を使い回す */
```

a 用・b 用の関数を二重に書かずに済み、`operations.c` は **5 関数 116 行**に収まっています。
`ft_double_shift` は内部で空文字列を渡して 2 本のスタックを回し、`rr` / `rrr` を 1 行だけ出力します。

### 貪欲な挿入ソートとコスト関数

`choose_resolve` が要素数で経路を分けます。2 要素なら `sa` を 1 回、3 要素なら `resolve_three` による
場合分けの決め打ち（最大 2 命令）、4 要素以上は汎用の `resolve_stack` へ進みます。汎用側は 4 段階です。

1. **退避**: 最後の 3 要素を残して全要素を B へ `pb` する。このとき `get_median` で求めた A の中央値と
   比較し、押し込んだ値が中央値より大きければ `rb` を打つ。B の内部が「中央値より大きい群 / 小さい群」に
   ゆるく二分され、後段の B 側の回転距離が縮む。
2. **基底**: A に残った 3 要素を `resolve_three` で確定させる。汎用側も同じ関数に委ねるため基底が 1 つに揃う。
3. **挿入ループ**: B の全要素についてコストを計算し、**最も安い 1 要素**を選んで A の正しい位置へ `pa` する。
   B が空になるまで繰り返す。
4. **仕上げ**: A の最小値が先頭に来るよう回転して終了。

コスト関数 `get_op_for_gplace` は、ある B の要素を A に戻す総手数をこう見積もります。

```
コスト = (B をその要素が上端に来るまで回す手数)
       + (A を挿入位置が上端に来るまで回す手数)
       - (両者が同方向で重なり rr / rrr に融合できる分)   ← get_coherences
       + 1                                                ← pa
```

回転方向は `get_op_for_topplace` が決めます。目標添字がスタックの中点より上か下かで `ra` 系 / `rra` 系を
選び、常に短い側へ回します。戻り値の符号で方向、絶対値で回数を表し、`r_top` が実際の命令列へ展開します。
A 側の挿入位置は、対象値が A の値域の外なら A の最小値の直前、値域内なら `get_min_above_tresh` で
「対象値より大きい要素のうち最小のもの」を探してその直前に置きます。
スタックを循環バッファとして扱うため、どちらの場合も正しい順序が保たれます。

**計算量**: 1 要素を戻すたびに B の全要素（O(n)）についてコストを計算し、その内部で `get_min_stack` などが
O(n) 走査するため 1 回の選択が O(n²)、これを n 回繰り返すので全体で **O(n³)** です。加えて回転 1 回が
配列シフトで O(n) かかります。操作回数の少なさと引き換えに実行時間を犠牲にした設計で、改善余地と認識しています。

### エラー処理

「検証を全部通してからソートを開始する」方針です。`ft_handle_errors` が引数形式と重複を先に確定させ、
ソート経路には検証コードが一切ありません。数値変換の失敗（`ft_atoi` が 0 を返したのに文字列が `"0"` でない）は
重複検出関数の中で兼ねて判定しています。受理するのは「数字と先頭の `-` のみ」なので、
`+5`・`00`・`-0` はいずれも `Error` です。

---

## ビルド・実行方法

```bash
$ make          # libft を再帰 make してから -L./libft -lft でリンク
$ ./push_swap 3 1 5 2 4
pb
pb
ra
pa
rra
rra
pa
rra
rra

$ ./push_swap "5 4 3 2 1"     # 1 引数のクォート文字列も同じように動く
pb
rb
pb
ra
sa
pa
ra
pa
ra

$ ./push_swap 1 2 3           # 整列済み → 出力なし
$ ./push_swap 1 2 a
Error
$ ./push_swap 1 1 2
Error
```

`Makefile` のターゲットは `all`（デフォルト）・`clean`・`fclean`・`re` の 4 つです。
コンパイルフラグは `-g -Wall -Wextra -Werror` で、警告ゼロで通ります。

ソースは `mandatory/push_swap.h` と `mandatory/srcs/` 配下の 7 本（`push_swap.c` / `errors_handling.c` /
`operations.c` / `utils_stack.c` / `algorithm.c` / `algorithm_helper.c` / `utils.c`）で計 798 行・33 関数です。
libft は submodule ではなくディレクトリごと同梱していますが、push_swap が実際に使うのは
`ft_atoi` / `ft_isdigit` / `ft_strncmp` / `ft_putstr_fd` / `ft_split_mult` 程度です。

---

## 検証

リポジトリにテストを同梱していないため、出力された操作列を Python の簡易シミュレータで再生し、
最終状態が「A が昇順・B が空」であることを外部から確認しました
（42 標準の `checker_*` バイナリと同じ役割を自前で用意した形です）。乱数シード 42、値域 ±100000 での実測:

| 要素数 | 試行数 | 操作回数 中央値 | 最大 | 誤り | 実行時間（中央値） |
| --- | --- | --- | --- | --- | --- |
| 3 | 200 | 1 | 2 | 0 | — |
| 5 | 200 | 8 | 12 | 0 | — |
| 100 | 200 | 573 | 640 | 0 | 0.021 s |
| 250 | — | — | — | — | 0.246 s |
| 500 | 20 | 4585 | 4787 | 0 | 2.703 s |

42 の評価基準（3 個で 3 手以下、5 個で 12 手以下、100 個で 700 手未満、500 個で 5500 手未満が最高点）に対し、
測定した全ケースが最高点の帯に収まりました。ただしこれは**実測分布であって最悪ケースの理論保証ではありません**。
実行時間は要素数 2 倍で約 11 倍の伸びで、上述の O(n³) + 回転 O(n) という見積もりと矛盾しません。

`norminette mandatory libft` は 78 ファイルすべて OK、エラー 0 件です。

---

## 既知の制限

正確を期すため、実装していない点・仕様と差がある点を明記します。

- **bonus（checker）は未実装**です。`mandatory/` のみで `bonus/` ディレクトリは存在しません。
- **`int` 範囲外の値を検査していません**。`ft_atoi` のラップアラウンドがそのまま通るため、
  `./push_swap 2147483648 1 2` は `-2147483648 1 2` と解釈され、整列済み扱いで何も出力しません。
- **`Error` は標準出力（fd 1）に出ます**。標準エラー出力ではありません。
- `.gitignore` がないため、`make` 後は `.o`・`libft.a`・バイナリが untracked として現れます。
- ヘッダに `show_stack` のプロトタイプが残っていますが定義はありません（デバッグ用の削除漏れ）。

---

## 学んだこと

**データ構造の選択がコードの形を決める。** 配列 + 番兵 + 自己保持 index という選択は、
「回転が O(n) になる」という代償と引き換えにメモリ管理をほぼ消し去りました。確保が 2 回・解放が 1 箇所しか
ない状態は、ソートロジックを書くときにエラー処理の分岐を考えなくてよいことを意味します。
連結リストなら回転は O(1) ですが、代わりに全操作にノード管理がつきます。どちらが正解かではなく、
**何を捨てて何を得たかを説明できること**が設計だと理解しました。

**重複を消す手段は抽象化だけではない。** 11 命令に対して 11 個の関数を書く代わりに、出力文字列を
パラメータにするだけで 5 関数に落ちました。新しい層を足すより、引数を 1 つ増やすほうが安く済む場合があります。

**貪欲法はコスト関数の設計がすべて。** 「B の上端から順に戻す」だけでも動きますが操作回数は大きく増えます。
`rr` / `rrr` への融合分をコストから引くという補正が結果を左右しており、
アルゴリズムの骨格よりも評価関数のほうが効いていました。そして操作回数は基準を満たす一方で実行時間は
O(n³) の見積もり通りに悪化しており、「操作回数の最適化」と「実行時間の最適化」が別物であることを
実測で確認できました。

---

42 Tokyo のカリキュラム課題として作成した学習成果物です。課題仕様は 42 の subject に準拠しています。
