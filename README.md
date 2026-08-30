# 「12ステップで作る組込みOS自作入門」の環境選定

## 必要要件

- 極力「12ステップで作る組込みOS自作入門」の内容を実現できること
- フラッシュROMの書き換えが可能(ブートローダーが自作可能)
- フラッシュROMの書き換えに専用のROMライタが不要
- GNUツール(gcc, binutils, gmakeなど)で開発ができること

## 選定マイコン：STM32F401RE (Nucleo-F401RE)

### ハードウェア仕様

| 項目 | 仕様 |
|-----|------|
| マイコン | STM32F401RE |
| プロセッサ | ARM Cortex-M4 (84 MHz) |
| フラッシュROM | 512 KB |
| SRAM | 96 KB |
| 開発ボード | NUCLEO-F401RE |
| 書き込みインターフェース | オンボードST-Link/V2-1 (SWD対応) |
| USB | ミニUSB (電源・通信・プログラミング) |

### 必要な開発環境

#### 1. GNUツールチェーン
- **arm-none-eabi-gcc** (ARMコンパイラ)
- **arm-none-eabi-binutils** (アセンブラ、リンカ等)

入手先：
- GNU ARM Embedded Toolchain (https://developer.arm.com/downloads/-/gnu-rm)
- または MinGW/MSYS2経由

バージョン：15.3.rel1

#### 2. STM32CubeProgrammer
フラッシュプログラミング用ツール
- フラッシュROMへのコード書き込み
- ST-Link経由での書き込み

#### 3. GNU make
ビルド自動化ツール

#### 4. Windows11 PowerShell
この環境は Windows11 の PowerShell から実行できる前提とする。
PowerShell から実行する環境として扱うため、Makefile 内のファイル操作などは Windows/PowerShell 環境でそのまま使えるコマンドに合わせる。

そのため、ファイルのコピーや削除には Unix 系の `cp` や `rm` ではなく、Windows 標準の `copy` や `del` を使用する。  
これにより、MSYS2 や Git Bash などの Unix 系シェルを前提にせず、PowerShell からビルド、書き込み、クリーンを実行できる。

### 開発ツールチェーン全体図

```
Source Code (C/Asm)
    ↓
arm-none-eabi-gcc (コンパイル)
    ↓
arm-none-eabi-ld (リンク)
    ↓
arm-none-eabi-objcopy (バイナリ生成)
    ↓
STM32CubeProgrammer (フラッシュに書き込み) → ST-Link/V2-1 → Nucleo-401RE
```

### 開発ワークフロー

1. **コード作成** → C言語 + インラインアセンブラ
2. **コンパイル・リンク** → Makefile使用
3. **フラッシュプログラミング** → STM32CubeProgrammer経由
4. **実行確認** → ボード上で動作確認

### 利点

- 本の要件をすべて満たす
- 無料で利用できるツール中心
- Windows/Linux/macOS対応
- USB 1本でプログラミング可能
- 現在の最新マイコンで学習可能
