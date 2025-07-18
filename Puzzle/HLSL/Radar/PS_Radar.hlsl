// C++側から設定されるデータ�@
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld; // ワールド行列
    matrix matView; // ビュー行列
    matrix matProj; // プロジェクション行列
    float4 color; // 色
    float4 time; // 時間
   
};

// C++側から設定されるデータ�A
Texture2D tex : register(t0); // テクスチャ1
SamplerState samLinear : register(s0); // サンプラーステート

// このシェーダが引数として受け取るデータ
struct PS_INPUT
{
    float4 pos : SV_POSITION; // 位置
    float2 Tex : TEXCOORD; // UV座標
};

float4 main(PS_INPUT input) : SV_TARGET
{
   
    
   
     // ピクセルの中心からの距離を計算（半径1の円形における距離）
    float distanceFromCenter = length(input.Tex - float2(0.5, 0.5));

    // グラデーションエフェクトの強度を距離に基づいて調整する
    float gradient = exp(-abs(sin(time.x * .050 + distanceFromCenter * -.050)));

    // テクスチャをサンプリング
    float4 output = tex.Sample(samLinear, input.Tex);
   // output.a = 0;
    
    // グラデーションエフェクトを加える
    // エフェクトの色は画像の色に加算
    output.rgb += gradient * color.rgb;

    // 結果を返す
    return output;
}

