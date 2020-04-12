// 各種プラグインのロード
const merge = require('webpack-merge');
const common = require('./webpack.common.js');

// 本番用の設定追加分
module.exports = merge(common[0], {
  mode: 'production',
  devtool: false,
});
