#### [Reach Service]() 底层接口说明

- SOF vs FJCA JS多CA版本

O|序号| RS接口 | SOF | FJCA | 硬件支持 |说明
---|--- | --- |--- |--- | ---| --
|1|RS_ConfigParameters|||x
|2|RS_GetParameters|||x
|3|RS_GreateQRCode|||x
|4|RS_GetTransid|||x
|5|RS_EncryptFile|||x|SM4算法 对称加密
|6|RS_DevryptFile|||x|SM4算法 对称解密
@|7|RS_GetUserList|+|+
@|8|RS_GetCertBase64String|+|+
@|9|RS_GetCertInfo||x
@|10|RS_CertLogin|
@|11|RS_GetPinRetryCount||x
|12|RS_ChangePassWd||x
|13|RS_VerifyIdentity|||x
@|14|RS_KeyGetKeySn|
|15|RS_KeyDigitalSignByP1|
|16|RS_VerifyDigitalSignByP1|||x
@|17|RS_KeySignByP1|
@|18|RS_VerifySignByP1|||x
@|19|RS_KeySignByP7|
@|20|RS_VerifySignByP7|||x
@|21|RS_KeyEncryptData|||x|公钥加密
@|22|RS_KeyDecryptData||||私钥解密
|23|RS_KeyEncryptByDigitalEnvelope|||x
|24|RS_KeyDecryptByDigitalEnvelope|

O|序号| RSCloud接口 |说明
---|--- | --- |---
|1|RS_CloudLoginAuth|
|2|RS_CloudGetAuth|
|3|RS_CloudSealAuth|
|4|RS_CloudGetSealList|
|5|RS_CloudSignByP7|
|6|RS_CloudGetSignResult|
|7|RS_CloudLogoutAuth|
|8|RS_CloudEncryptAuth|
|9|RS_CloudEncryptData|
|10|RS_CloudDevryptAuth|
|11|RS_CloudDevryptData|
|12|RS_CloudReceiveDevryptResult|
|13|RS_CloudLogout|

O|序号| RSEvent接口 |说明
---|--- | --- |---
|1|RS_CloudLoginAuthEvent|
|2|RS_CloudSealAuthEvent|
|3|RS_CloudGetSignResultEvent
|4|RS_CloudEncAuthEvent|
|5|RS_CloudDevAuthEvent|


<escape>
<table class="tg">
  <tr>
    <th></th>
    <th></th>
    <th></th>
    <th></th>
    <th></th>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
</table>
</escape>
