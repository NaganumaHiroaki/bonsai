## 競技プログラミングのライブラリ

各アルゴリズムはクラスで実装されており, 実際に用いる際にはそのクラスと依存ライブラリ等をコピーして使用する. どこからコピーすれば良いかはコメントアウト部分を見ればよく, 依存ライブラリは`// Need start`から`// Need end`までの部分を, クラスは`// Copy start`から`// Copy end`までの部分を切り取れば良い.

* 作成済み
    * アルゴリズム
        * Dijkstra
        * Bellmanford
        * Warshall-Floyd
    * データ構造
        * Union-Find
        * BIT（SumBIT, RangeMinimumQueryBIT, RangeMaxQueryBIT）
        * セグメント木（RangeMinimumQuerySegmentTree）
    * 幾何
        * 二次元座標の構造体
        * 凸包（グラハムスキャン）