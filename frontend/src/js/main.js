// ###################################################################
//    JS エントリーポイント
// ###################################################################
import '../../node_modules/popper.js/dist/umd/popper.min.js';
import '../../node_modules/bootstrap/dist/js/bootstrap.min.js';
import '../../node_modules/@coreui/coreui/dist/js/coreui.min.js';
const $ = require('../../node_modules/jquery/dist/jquery.min.js');

// 以下のJSファイル内に apiServerURLBase の定義が必要
const Settings = require('./settings.js');

$(() => {
  $('.js-remote-button').on('click', e => {
    const buttonName = $(e.currentTarget).data('codename');

    fetch(`${Settings.apiServerURLBase}send?button=${buttonName}`, {
      method: 'GET',
      mode: 'cors'
    }).then(response => {
      if (response.ok) {
        // 成功時: アラートクリア
        $('.alert').remove();
      } else {
        // エラー発生時: アラート表示
        $('html, body').animate({ scrollTop: 0 });
        $('.js-card-title').after(
          $('<div class="alert alert-danger">')
            .text('赤外線の送信に失敗しました。M5StickC の電源およびLCDディスプレイを確認して下さい。')
            .append(
              $('<button type="button" class="close" data-dismiss="alert" aria-label="閉じる">')
                .append(
                  $('<span aria-hidden="true">')
                    .html('&times;')
                )
            )
        );
      }
    });

    return false;
  });
});
