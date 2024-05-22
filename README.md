# OPLx-TimbreEditor
YAMAHA の FM音源チップ OPL系用の音色エディターです。

実行ファイルのダウンロードは[こちら](https://github.com/DM-88mkII/OPLx-TimbreEditor/blob/main/OPLx-TimbreEditor/x64/Release/OPLx-TimbreEditor.exe)  

<br>

# 特徴
* キーボード操作志向で、素早いエディットが可能
* レイヤーに対応
  * 複数の音色を同時にプレビュー可能
* FNumberを活用したオクターブ拡張
  * o0c ～ o9f+ まで、幅広い音域で発音可能
  * 高マルチプルな音色も、適正音域で発音可能
* 強制ダンプ機能（YM3526モード時）
  * 音色のプレビューで、CL(カレントレベル)を無音の状態から発音
  * 音色のアタック部の作り込みに便利
* 拡張コピーに対応（以下の形式に対応）
  * MGSDRV,MSXplay
  * mml2vgm（LL形式）
  * MSX-BASIC
* ペーストは、上記全ての形式を自動判別してインポート

<br>

# 操作方法
|キー|効果|
|:-:|:-:|
|↑,↓,←,→|パラメータ項目の移動|
|PageUp,PageDown|パラメータの値を1ずつ上下|
|Shift + (PageUp,PageDown)|パラメータの値を10ずつ上下|
|'-',0,1,2,3,4,5,6,7,8,9,Space,BackSpace|パラメータの編集|
|Enter|パラメータの編集/決定|
|Ctrl + z|パラメータのアンドゥ/リドゥ|
|Ctrl + r|オペレータのローテート（※）|
|ESC|パラメータ編集/オペレータローテートのキャンセル|
|Ctrl + (Insert,Delete)|レイヤータブの追加/削除|
|Ctrl + (←,→)|レイヤータブの移動|
|z,s,x,d,c,v,g,b,h,n,j,m,','|現レイヤーの音色をプレビュー|
|Shift + (z,s,x,d,c,v,g,b,h,n,j,m,',')|全レイヤーの音色をプレビュー|
|Home,End|プレビューのオクターブを1ずつ上下|
|Ctrl + (c,v)|通常コピー（OPLx形式の音色データ）|
|Ctrl + Shift + (c,v)|拡張コピー（Setting形式の音色データ）|
|Ctrl + (o,s)|音色のロード/セーブ|

（※）一回目で移動元オペレータの選択、二回目で移動先オペレータの選択  

<br>

# 音色
## コントロール部
|パラメータ|効果|
|:-:|:-:|
|CON（◎）|コネクション|
|FB|フィードバック|
|NUM|外部ツール連携の為の音色番号|
|KML（※）|キーマップ下限|
|KMH（※）|キーマップ上限|
|EN|発音の有効/無効|
|FDE（◎）|強制ダンプの有効/無効|
|SEL（◎）|ノートセレクト|
|AMD（◎）|振幅変調深度|
|PMD（◎）|位相変調深度|
|KT|キートランスポーズ|
|FDT|FNumberデチューン|
|OPLL|YM2413モードの有効/無効|
|INST（☆）|音色番号|
|VOL（☆）|ボリューム|
|SUS（☆）|サスティンの有効/無効|

（※）プレビュー時、ノートナンバーがキーマップ範囲内であれば発音します。  
（◎）YM3526モードの場合のみ。  
（☆）YM2413モードの場合のみ。  

## オペレータ部
|パラメータ|効果|
|:-:|:-:|
|AR|アタックレート|
|DR|ディケイレート|
|SL|サスティンレベル|
|RR|リリースレート|
|KSL|キースケールレベル|
|TL|トータルレベル（☆OP1のみ有効）|
|MT|マルチプル|
|AM|振幅変調の有効/無効|
|VIB|ビブラートの有効/無効|
|EGT|エンベロープジェネレートタイプ|
|KSR|キースケールレート|
|WF（☆）|波形|

（※）効果音モードが有効な場合に機能します。  
（☆）YM2413モードの場合のみ。  
