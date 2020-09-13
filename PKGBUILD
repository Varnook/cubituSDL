pkgname=cubitu
pkgver=0.1
pkgrel=1
pkgdesc='un cubitu :)'
url='https://github.com/Varnook/cubituSDL'
arch=('x86_64')
depends=('sdl2')
source=("https://github.com/Varnook/cubituSDL")

build() {
	cd "$pkgname-$pkgver"
	./configure --prefix=/usr
	make
}

package() {
	cd "$pkgname-$pkgver"
	sudo make DESTDIT="$pkgdir/" install
}
