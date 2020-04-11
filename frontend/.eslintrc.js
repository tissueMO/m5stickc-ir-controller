module.exports = {
  env: {
    browser: true,
    es6: true
  },
  extends: [
    "standard",
    "eslint:recommended"
  ],
  globals: {
    Atomics: "readonly",
    SharedArrayBuffer: "readonly"
  },
  parserOptions: {
    ecmaVersion: 2018
  },
  rules: {
    // セミコロンは冗長であってもよいので基本的に付ける
    "semi": ["error", "always"],
    "semi-spacing": ["error", {"after": true, "before": false}],
    "semi-style": ["error", "last"],
    "no-extra-semi": "error",
    "no-unexpected-multiline": "error",
    "no-unreachable": "error",

    // 不等号は常に小なりを基本として向きを揃えるため yoda 記法を暗黙的かつ条件付きで認める
    "yoda": "off",

    // Chart.js でグラフを描画する際に怒られるのを防ぐ
    "no-new": "off",
  }
}
