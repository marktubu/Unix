---
title: Unity Shader 内置变量
date: 2019-09-11 11:16:43
categories:
- Unity
tags: Unity
---
</br></br></br>Unity Shader 内置变量总结，方便查阅
</br></br></br>#### 转换相关变量（矩阵）
</br></br></br>类型都是 float4x4
</br>|                | **Name**            | **Value**                                 |
| -------------- | ------------------- | ----------------------------------------- |
| 模型 >> 投影   | UNITY_MATRIX_MVP    | Current model * view * projection matrix. |
| 模型 >> 相机   | UNITY_MATRIX_MV     | Current model * view matrix.              |
| 世界 >> 相机   | UNITY_MATRIX_V      | Current view matrix.                      |
| 相机 >> 投影   | UNITY_MATRIX_P      | Current projection matrix.                |
| 世界 >> 投影   | UNITY_MATRIX_VP     | Current view * projection matrix.         |
| MV的转置矩阵   | UNITY_MATRIX_T_MV   | Transpose of model * view matrix.         |
| MV的逆转置矩阵 | UNITY_MATRIX_IT_MV  | Inverse transpose of model * view matrix. |
| 模型 >> 世界   | unity_ObjectToWorld | Current model matrix.                     |
| 世界 >> 模型   | unity_WorldToObject | Inverse of current world matrix.          |
</br>​
</br>​
</br>#### 相机和屏幕相关变量
</br></br></br>| **Name**                       | **Type** | **Value**                                                    |
| :----------------------------- | :------- | ------------------------------------------------------------ |
| _WorldSpaceCameraPos           | float3   | World space position of the camera.                          |
| _ProjectionParams              | float4   | `x` is 1.0 (or –1.0 if currently rendering with a [flipped projection matrix](https://docs.unity3d.com/Manual/SL-PlatformDifferences.html)), `y` is the camera’s near plane, `z` is the camera’s far plane and `w` is 1/FarPlane. |
| _ScreenParams                  | float4   | `x` is the width of the camera’s target texture in **pixels** , `y` is the height of the camera’s target texture in pixels, `z` is 1.0 + 1.0/width and `w` is 1.0 + 1.0/height. |
| _ZBufferParams                 | float4   | Used to linearize Z buffer values. `x` is (1-far/near), `y` is (far/near), `z` is (x/far) and `w` is (y/far). |
| unity_OrthoParams              | float4   | `x` is orthographic camera’s width, `y` is orthographic camera’s height, `z` is unused and `w` is 1.0 when camera is orthographic, 0.0 when perspective. |
| unity_CameraProjection         | float4x4 | Camera’s projection matrix.                                  |
| unity_CameraInvProjection      | float4x4 | Inverse of camera’s projection matrix.                       |
| unity_CameraWorldClipPlanes[6] | float4   | Camera frustum plane world space equations, in this order: left, right, bottom, top, near, far. |
</br></br></br>​
</br>#### 时间相关变量
</br></br></br>| **Name**        | **Type** | **Value**                                                    |
| :-------------- | :------- | ------------------------------------------------------------ |
| _Time           | float4   | Time since level load (t/20, t, tx2, tx3), use to animate things inside the shaders. |
| _SinTime        | float4   | Sine of time: (t/8, t/4, t/2, t).                            |
| _CosTime        | float4   | Cosine of time: (t/8, t/4, t/2, t).                          |
| unity_DeltaTime | float4   | Delta time: (dt, 1/dt, smoothDt, 1/smoothDt).                |
</br></br></br></br></br>#### 光照相关变量
</br></br></br>> Light参数以不同的方式传递给着色器，具体取决于渲染路径使用，以及在着色器中使用哪个LightMode Pass Tag。
</br></br></br>##### 前向渲染 （ForwardBase 和 ForwardAdd pass 类型）
</br>| **Name**                                                | **Type**    | **Value**                                                    |
| ------------------------------------------------------- | ----------- | ------------------------------------------------------------ |
| _LightColor0 *(declared in Lighting.cginc)*             | fixed4      | Light color.                                                 |
| _WorldSpaceLightPos0                                    | float4      | Directional lights: (world space direction, 0). Other lights: (world space position, 1). |
| _LightMatrix0 *(declared in AutoLight.cginc)*           | float4x4    | World-to-light matrix. Used to sample cookie & attenuation textures. |
| unity_4LightPosX0, unity_4LightPosY0, unity_4LightPosZ0 | float4      | *(ForwardBase pass only)* world space positions of first four non-important point lights. |
| unity_4LightAtten0                                      | float4      | *(ForwardBase pass only)* attenuation factors of first four non-important point lights. |
| unity_LightColor                                        | half4[4]    | *(ForwardBase pass only)* colors of of first four non-important point lights. |
| unity_WorldToShadow                                     | float4x4[4] | World-to-shadow matrices. One matrix for spot lights, up to four for directional light cascades. |
</br></br></br></br></br>##### 延迟着色和延迟光照相关变量
</br></br></br>用在 lighting pass 着色器中（定义在UnityDeferredLibrary.cginc中）
</br>| **Name**            | **Type**    | **Value**                                                    |
| :------------------ | :---------- | :----------------------------------------------------------- |
| _LightColor         | float4      | Light color.                                                 |
| _LightMatrix0       | float4x4    | World-to-light matrix. Used to sample cookie & attenuation textures. |
| unity_WorldToShadow | float4x4[4] | World-to-shadow matrices. One matrix for spot lights, up to four for directional light cascades. |
</br></br>
</br></br>
</br>##### Vertex-Lit 渲染路径下的相关变量
</br></br>
</br>> 关于 Vertex-Lit渲染路径：Vertex Lit路径通常在一个 pass 中渲染每个对象，并为每个顶点计算所有灯光的光照。它是最快的渲染路径，并且拥有最多的硬件支持。但由于光照计算在顶点级别，它不支持大多数逐像素效果：阴影，法线贴图，灯管烘焙（light cookies），高精细度的镜面高光都不被支持。
</br>最多可为 Vertex pass 类型设置8个灯;始终从最亮的一个开始排序。因此，如果要同时渲染受两个灯影响的对象，则可以在数组中前两个条目。如果影响对象的光线少于8，则其余部分的颜色将设置为黑色。
</br></br>
</br>| **Name**            | **Type**  | **Value**                                                    |
| :------------------ | :-------- | ------------------------------------------------------------ |
| unity_LightColor    | half4[8]  | Light colors.                                                |
| unity_LightPosition | float4[8] | View-space light positions. (-direction,0) for directional lights; (position,1) for point/spot lights. |
| unity_LightAtten    | half4[8]  | Light attenuation factors. *x* is cos(spotAngle/2) or –1 for non-spot lights; *y* is 1/cos(spotAngle/4) or 1 for non-spot lights; *z* is quadratic attenuation; *w* is squared light range. |
| unity_SpotDirection | float4[8] | View-space spot light positions; (0,0,1,0) for non-spot lights. |
</br></br>
</br></br>
</br>#### 雾和环境（Ambient）相关变量
</br></br>
</br>| **Name**                 | **Type** | **Value**                                                    |
| ------------------------ | -------- | ------------------------------------------------------------ |
| unity_AmbientSky         | fixed4   | Sky ambient lighting color in gradient ambient lighting case. |
| unity_AmbientEquator     | fixed4   | Equator ambient lighting color in gradient ambient lighting case. |
| unity_AmbientGround      | fixed4   | Ground ambient lighting color in gradient ambient lighting case. |
| UNITY_LIGHTMODEL_AMBIENT | fixed4   | Ambient lighting color (sky color in gradient ambient case). Legacy variable. |
| unity_FogColor           | fixed4   | Fog color.                                                   |
| unity_FogParams          | float4   | Parameters for fog calculation: (density / sqrt(ln(2)), density / ln(2), –1/(end-start), end/(end-start)). *x* is useful for Exp2 fog mode, *y* for Exp mode, *z* and *w* for Linear mode. |
</br></br>
</br></br>
</br>#### 其他变量
</br></br>
</br>| **Name**          | **Type** | **Value**                                                    |
| :---------------- | :------- | ------------------------------------------------------------ |
| unity_LODFade     | float4   | Level-of-detail fade when using [LODGroup](https://docs.unity3d.com/Manual/class-LODGroup.html). *x* is fade (0..1), *y* is fade quantized to 16 levels, *z* and *w* unused. |
| _TextureSampleAdd | float4   | Set automatically by Unity **for UI only** based on whether the texture being used is in Alpha8 format (the value is set to (1,1,1,0)) or not (the value is set to (0,0,0,0)). |
</br></br>