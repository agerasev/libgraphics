function __gfxInit(canvas) {
	__gfx_cnv = canvas;
	__gfx_ctx = canvas.getContext('2d');
	__gfx_map = new Array(1.0,0.0,0.0,1.0,0.0,0.0);
}

function __gfxDispose() {
	__gfx_ctx = undefined;
	__gfx_cnv = undefined;
}

function __gfxUpdateMap() {
	var m = __gfx_map;
	//__gfx_ctx.resetTransform();
	__gfx_ctx.setTransform(m[0], m[1], m[2], m[3], 0.5*__gfx_cnv.width + m[4], 0.5*__gfx_cnv.height - m[5]);
}

function __gfxTranslate(x, y) {
	var m = __gfx_map;
	m[4] = x; m[5] = y;
	__gfxUpdateMap();
}

function __gfxTransform(m00, m01, m10, m11) {
	var m = __gfx_map;
	m[0] = m00; m[1] = m01;
	m[2] = m10; m[3] = m11;
	__gfxUpdateMap();
}

function __gfxClear() {
	__gfx_ctx.resetTransform();
	__gfx_ctx.clearRect(0, 0, __gfx_cnv.width, __gfx_cnv.height);
	__gfxUpdateMap();
}

function __gfxFill() {
	__gfx_ctx.resetTransform();
	__gfx_ctx.fillRect(0, 0, __gfx_cnv.width, __gfx_cnv.height);
	__gfxUpdateMap();
}

function __gfxDrawCircle() {
	__gfx_ctx.beginPath();
    __gfx_ctx.arc(0, 0, 1, 0, Math.PI*2, true);
    __gfx_ctx.fill();
}
