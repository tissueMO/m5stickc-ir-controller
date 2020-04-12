// 各種プラグインのロード
const path = require('path');
const merge = require('webpack-merge');
const common = require('./webpack.common.js');

// ビルド先パス
const DEST_PATH = path.join(__dirname, './public');

// 開発用の設定追加分
module.exports = merge(common[0], {
  mode: 'development',
  devtool: 'source-map',
  devServer: {
    contentBase: DEST_PATH,
    port: 3000,
    host: '0.0.0.0',
    disableHostCheck: true,
    watchContentBase: true,
    open: true,
  },
})
