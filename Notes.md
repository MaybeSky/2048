# 笔记
## 原项目的Reverse Engineering
项目地址：[https://github.com/gabrielecirulli/2048](https://github.com/gabrielecirulli/2048)

### CSS3动画
* [阮一峰的教程](http://www.ruanyifeng.com/blog/2014/02/css_transition_and_animation.html)
* [TimingFunction的官方定义](https://www.w3.org/TR/2012/WD-css3-transitions-20120403/#transition-timing-function)
* WebKit对cubic-bezier TimingFunction的实现：
	* [class UnitBezier](https://github.com/WebKit/webkit/blob/67985c34ffc405f69995e8a35f9c38618625c403/Source/WebCore/platform/graphics/UnitBezier.h)
	* [solveCubicBezierFunction()](https://github.com/WebKit/webkit/blob/9eec3ca633a72d2cf629895a68f4afda1bdcd47c/Source/WebCore/page/animation/AnimationBase.cpp#L58)
* [SASS中颜色混合函数（mix）的实现](https://github.com/sass/sass/blob/4415d51997bf6c2da7f0b01d2dd9d5925ef9724d/lib/sass/script/functions.rb#L1291)
* [SASS颜色函数的教程](http://www.w3cplus.com/preprocessor/sass-color-function.html)

## 此项目
* [WebKit编码规范](https://webkit.org/code-style-guidelines/)
* [Lazy Foo' Productions - Color Keying](http://lazyfoo.net/tutorials/SDL/10_color_keying/index.php) 此文讲解了Texture类的创建
* [Lazy Foo' Productions - Render to Texture](http://lazyfoo.net/tutorials/SDL/43_render_to_texture/index.php)
