// Dynamic Adapt v.1
// HTML data-da="where(uniq class name),position(digi),when(breakpoint)"
// e.x. data-da="item,2,992"
// Andrikanych Yevhen 2020
// https://www.youtube.com/c/freelancerlifestyle

"use strict";

(function () {
	let originalPositions = [];
	let daElements = document.querySelectorAll('[data-da]');
	let daElementsArray = [];
	let daMatchMedia = [];
	//Заполняем массивы
	if (daElements.length > 0) {
		let number = 0;
		for (let index = 0; index < daElements.length; index++) {
			const daElement = daElements[index];
			const daMove = daElement.getAttribute('data-da');
			if (daMove != '') {
				const daArray = daMove.split(',');
				const daPlace = daArray[1] ? daArray[1].trim() : 'last';
				const daBreakpoint = daArray[2] ? daArray[2].trim() : '767';
				const daType = daArray[3] === 'min' ? daArray[3].trim() : 'max';
				const daDestination = document.querySelector('.' + daArray[0].trim())
				if (daArray.length > 0 && daDestination) {
					daElement.setAttribute('data-da-index', number);
					//Заполняем массив первоначальных позиций
					originalPositions[number] = {
						"parent": daElement.parentNode,
						"index": indexInParent(daElement)
					};
					//Заполняем массив элементов 
					daElementsArray[number] = {
						"element": daElement,
						"destination": document.querySelector('.' + daArray[0].trim()),
						"place": daPlace,
						"breakpoint": daBreakpoint,
						"type": daType
					}
					number++;
				}
			}
		}
		dynamicAdaptSort(daElementsArray);

		//Создаем события в точке брейкпоинта
		for (let index = 0; index < daElementsArray.length; index++) {
			const el = daElementsArray[index];
			const daBreakpoint = el.breakpoint;
			const daType = el.type;

			daMatchMedia.push(window.matchMedia("(" + daType + "-width: " + daBreakpoint + "px)"));
			daMatchMedia[index].addListener(dynamicAdapt);
		}
	}
	//Основная функция
	function dynamicAdapt(e) {
		for (let index = 0; index < daElementsArray.length; index++) {
			const el = daElementsArray[index];
			const daElement = el.element;
			const daDestination = el.destination;
			const daPlace = el.place;
			const daBreakpoint = el.breakpoint;
			const daClassname = "_dynamic_adapt_" + daBreakpoint;

			if (daMatchMedia[index].matches) {
				//Перебрасываем элементы
				if (!daElement.classList.contains(daClassname)) {
					let actualIndex = indexOfElements(daDestination)[daPlace];
					if (daPlace === 'first') {
						actualIndex = indexOfElements(daDestination)[0];
					} else if (daPlace === 'last') {
						actualIndex = indexOfElements(daDestination)[indexOfElements(daDestination).length];
					}
					daDestination.insertBefore(daElement, daDestination.children[actualIndex]);
					daElement.classList.add(daClassname);
				}
			} else {
				//Возвращаем на место
				if (daElement.classList.contains(daClassname)) {
					dynamicAdaptBack(daElement);
					daElement.classList.remove(daClassname);
				}
			}
		}
		customAdapt();
	}

	//Вызов основной функции
	dynamicAdapt();

	//Функция возврата на место
	function dynamicAdaptBack(el) {
		const daIndex = el.getAttribute('data-da-index');
		const originalPlace = originalPositions[daIndex];
		const parentPlace = originalPlace['parent'];
		const indexPlace = originalPlace['index'];
		const actualIndex = indexOfElements(parentPlace, true)[indexPlace];
		parentPlace.insertBefore(el, parentPlace.children[actualIndex]);
	}
	//Функция получения индекса внутри родителя
	function indexInParent(el) {
		var children = Array.prototype.slice.call(el.parentNode.children);
		return children.indexOf(el);
	}
	//Функция получения массива индексов элементов внутри родителя 
	function indexOfElements(parent, back) {
		const children = parent.children;
		const childrenArray = [];
		for (let i = 0; i < children.length; i++) {
			const childrenElement = children[i];
			if (back) {
				childrenArray.push(i);
			} else {
				//Исключая перенесенный элемент
				if (childrenElement.getAttribute('data-da') == null) {
					childrenArray.push(i);
				}
			}
		}
		return childrenArray;
	}
	//Сортировка объекта
	function dynamicAdaptSort(arr) {
		arr.sort(function (a, b) {
			if (a.breakpoint > b.breakpoint) { return -1 } else { return 1 }
		});
		arr.sort(function (a, b) {
			if (a.place > b.place) { return 1 } else { return -1 }
		});
	}
	//Дополнительные сценарии адаптации
	function customAdapt() {
		//const viewport_width = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
	}
}());

/*
let block = document.querySelector('.click');
block.addEventListener("click", function (e) {
	alert('Все ок ;)');
});
*/

//Объявляем переменные
const parent_original = document.querySelector('.content__blocks_city');
const parent = document.querySelector('.content__column_river');
const item = document.querySelector('.content__block_item');
//Слушаем изменение размера экрана
window.addEventListener('resize', move);
//Функция
function move(m){
    if(!item) return
	const viewport_width = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
	if (viewport_width <= m ) {
		if (!item.classList.contains('done')) {
			parent.insertBefore(item, parent.children[2]);
			item.classList.add('done');
		}
	} else {
		if (item.classList.contains('done')) {
			parent_original.insertBefore(item, parent_original.children[2]);
			item.classList.remove('done');
		}
	}
}
//Вызываем функцию
move(992);

window.mobileCheck = function() {
    let check = false;
    (function(a){if(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0,4))) check = true;})(navigator.userAgent||navigator.vendor||window.opera);
    return check;
}
window.mobileAndTabletCheck = function() {
    let check = false;
    (function(a){if(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino|android|ipad|playbook|silk/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0,4))) check = true;})(navigator.userAgent||navigator.vendor||window.opera);
    return check;
};
let isMobile = false
let isTablet = false

if(window.mobileCheck()){
    isMobile = true
    if(window.mobileAndTabletCheck()){
        isTablet = true
    }
    //console.log('Mobile computer')
}
else {
    //console.log('desltop computer')
}

if(isMobile){
    let menuParents = document.querySelectorAll('.menu-page__parent > a')
    for(let index = 0; index < menuParents.length; index++) {
        let menuParent = menuParents[index]
        menuParent.addEventListener('click', (e) => {
        menuParent.parentElement.classList.toggle('_active') 
        e.preventDefault()
        })
    }
}
else {
    let menuParents = document.querySelectorAll('.menu-page__parent')
    let subMenus = document.querySelectorAll('.menu-page__link')

    for(let index = 0; index < menuParents.length; index++) {
        let menuParent = menuParents[index]
        let subMenu = subMenus[index]
        let ok = null
        subMenu.addEventListener('mouseenter', (e) => {
            ok = 'ok'
            //console.log(ok)
        })
        menuParent.addEventListener('mouseenter', function(e){
            //e.preventDefault()
            if(ok === 'ok')menuParent.classList.toggle('_active')
        })
        menuParent.addEventListener('mouseleave', (e) => {
            menuParent.classList.remove('_active') 
        })
    }
}
let user_icon = document.querySelector('.user-header__icon');
user_icon.addEventListener("click", function(e){
    let user_menu = document.querySelector('.user-header__menu');
    user_menu.classList.toggle('_active');
    
});

function body_lock (d){
    let body = document.querySelector('body');
	setTimeout(()=>{
		body.classList.add('_wait');
	},d)
}

let iconMenu = document.querySelector('.icon-menu');

if(iconMenu != null){
    let delay = 500;
    let body = document.querySelector('body');
    let menuBody = document.querySelector('.menu__body');
    iconMenu.addEventListener("click",(e) => {
    iconMenu.classList.toggle('_active');
    menuBody.classList.toggle('_active');    
    });
}

let iconMenuPage = document.querySelector('.page-icon');

if(iconMenuPage != null){
    let delay = 500;
    let body = document.querySelector('body');
    let menuBodyPage = document.querySelector('.menu-page__body');
    iconMenuPage.addEventListener("click",(e) => {
    iconMenuPage.classList.toggle('_active');
    menuBodyPage.classList.toggle('_active');    
    });
}

//menu page


//select

let searchSelectTitle = document.querySelector('.search-page__title')
let searchSelect = document.querySelector('.search-page__select')
searchSelectTitle.addEventListener('click', function(e){
    searchSelectTitle.parentElement.classList.toggle('_active')
})
//categories
let checkBoxCategories = document.querySelectorAll('.categories-search__checkbox')
for(let index = 0; index < checkBoxCategories.length; index++){
    const checkBoxCategory = checkBoxCategories[index]
    checkBoxCategory.addEventListener('change', function(e){
        checkBoxCategory.classList.toggle('_choice')

        let checkBoxActiveCategories = document.querySelectorAll('.categories-search__checkbox._choice')
        
        if(checkBoxActiveCategories.length > 0 ) {
            searchSelectTitle.classList.add('_cat')
            let quant = searchSelectTitle.querySelector('.choice-quant')
            quant.innerHTML = quant.getAttribute('data-text') + ' ' + checkBoxActiveCategories.length
        } else {
            searchSelectTitle.classList.remove('_cat')
        }
    })

}
const swcon = '._swiper'
//BuildSlider
let sliders = document.querySelectorAll('._swiper')
if(sliders) {
    for(let index = 0; index < sliders.length; index++){
        let slider = sliders[index]
        if(!slider.classList.contains('swiper-build')){
            let slider_items = slider.children
            if(slider_items) {
                for(let index = 0; index < slider_items.length; index++) {
                    let el = slider_items[index]
                    el.classList.add('swiper-slide')
                }
            }
            let slider_content = slider.innerHTML
            let slider_wrapper = document.createElement('div')
            slider_wrapper.classList.add('swiper-wrapper')
            slider_wrapper.innerHTML = slider_content
            slider.innerHTML = ''
            slider.appendChild(slider_wrapper)
            slider.classList.add('swiper-build')
        }
    }
    sliders_build_callback()
}

//ibg

function ibg() {
    let ibg = document.querySelectorAll('._ibg')
    for(let i = 0; i < ibg.length; i++){
        if(ibg[i].querySelector('img')) {
            ibg[i].style.backgroundImage = 'url("' + ibg[i].querySelector('img') .getAttribute('src') + '")'
        }
    }
    // ibg.map((ib) => {
    //     img = ib.querySelector('img')
    //     if(img){
    //         ib.style.backgroundImage = 'url(' + img .getAttribute('src') + ')'
    //     }
    // })
}
ibg()

function sliders_build_callback(params) {}
// const nsl = 1
// const spbetw = 0
// const spg = 1
// const speed = 800
// const loop = false
// const pagntype = 'bullet'
// const clkabl = true
// const obsPars =true
// const autoH = true
//const swpgn = '.mainslider__dotts'


if(document.querySelector('.mainslider')){
    let mainslider = new Swiper('.mainslider__body',{
    slidesPerView: 1,
    spaceBetween: 0,
    observe: true,
    observeParents: false,
    autoHeight: true,
    speed: 800,
    pagination: {
        el: '.mainslider__dotts',
        clickable: true
    },
    // navigation: {
    //     nextEl: '',
    //     prevEl: '',
    // }
    
    })
}

// const nextel = '.products-slider__arrow_next'
// const prevel = '.products-slider__arrow_prev'

if(document.querySelector('products-slide')){
    
    let productsSlider = new Swiper('.products-slider__item',{
        slidesPerView: 1,
        spaceBetween: 0,
        observe: true,
        observeParents: false,
        autoHeight: true,
        speed: 800,
        pagination: {
            el: '.products-slider__info',
            type: 'fraction'
            
        },
        navigation: {
            nextEl: '.products-slider__arrow_next',
            prevEl: '.products-slider__arrow_prev'
        }
    })
}

let mainsliderImages = document.querySelectorAll('.mainslider__image')
let mainsliderDotts = document.querySelectorAll('.mainslider__dotts .swiper-pagination-bullet')
let mainsliderImage = ''
    for(let index = 0; index < mainsliderImages.length; index++) {
        mainsliderImage = mainsliderImages[index].querySelector('img').getAttribute('src')
        mainsliderDotts[index].style.backgroundImage = "url('" + mainsliderImage + "')"
        mainsliderImage = ''
        //console.log(mainsliderImage)
    }

    let nsl = 1
    let spbetw = 20
    let spg = 1
    let speed = 800
    let loop = false
    let pagntype = 'bullet'
    let clkabl = true
    let obsPars = false
    let autoH = true
    let swpgn = '.mainslider__dotts'
    let nextel = ''
    let prevel = ''
    
function madeSwiper(swcon,bp = false){
    let swiper = null
    if(bp){
        swiper = new Swiper( swcon, {
            slidesPerView: nsl,
            spaceBetween: spbetw,
            slidesPerGroup: spg,
            observeParents: obsPars,
            loop: loop,
            autoHeight: autoH,
            speed: speed,
            loopFillGroupWithBlank: loop,
            pagination: {
                el: swpgn,
                clickable: clkabl,
                type: pagntype,
            },
            navigation: {
                nextEl: nextel,
                prevEl: prevel
            },
            breakpoints: {
                320: {
                    slidesPerView: 1,
                    spaceBetween: 0,
                    autoHeight: true
                },
                480: {
                    slidesPerView: 2,
                    spaceBetween: spbetw,
                    autoHeight: autoH
                },
                600: {
                    slidesPerView: 3,
                    spaceBetween: spbetw,
                    autoHeight: autoH
                },
                768: {
                    slidesPerView: 4,
                    spaceBetween: spbetw,
                    autoHeight: autoH
                },
                992: {
                    slidesPerView: 5,
                    spaceBetween: spbetw,
                    autoHeight: autoH
                }
    
            }
        });
    } 
    else {
        swiper = new Swiper( swcon, {
            slidesPerView: nsl,
            spaceBetween: spbetw,
            slidesPerGroup: spg,
            observeParents: obsPars,
            loop: loop,
            autoHeight: autoH,
            speed: speed,
            loopFillGroupWithBlank: loop,
            pagination: {
                el: swpgn,
                clickable: clkabl,
                type: pagntype,
            },
            navigation: {
                nextEl: nextel,
                prevEl: prevel
            }
        });
    }
}

madeSwiper('.mainslider__body')

nsl = 1
pagntype = 'fraction'
swpgn = '.products-slider__info'
nextel = '.products-slider__arrow_next'
prevel = '.products-slider__arrow_prev'
madeSwiper('.products-slider__item')

nsl = 5
spg = 1
loop = false
nextel = '.brands-slider__arrow_next'
prevel = '.brands-slider__arrow_prev'
madeSwiper('.brands-slider__body', true)

//noUislider
//const priceSlider = document.querySelector('.price-filter__slider')

// noUiSlider.create(priceSlider, {
    // start:[0,100000],
    // connect: true,
    // tooltips: [true, true],
    // range: {
        // 'min': [0],
        // 'max': [200000]
    // }
// })
// setButton.addEventListener('click', function(){
//     animateSlider.noUiSlider.set(60)
//     unAnimateSlider.noUiSlider.set(60)
// })