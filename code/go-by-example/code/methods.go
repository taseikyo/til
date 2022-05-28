/**
 * @date    2021-01-19 16:15:11
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 调用方法时，Go 会自动处理值和指针之间的转换。
 * 想要避免在调用方法时产生一个拷贝，或者想让方法可以修改接受结构体的值，
 * 你都可以使用指针来调用方法
 */

package main

import "fmt"

type rect struct {
	width, height int
}

func (r *rect) area() int {
	return r.width * r.height
}

func (r rect) perim() int {
	return 2*r.width + 2*r.height
}

func main() {
	r := rect{width: 10, height: 5}

	fmt.Println("area: ", r.area())
	fmt.Println("perim:", r.perim())

	rp := &r
	fmt.Println("area: ", rp.area())
	fmt.Println("perim:", rp.perim())
}
