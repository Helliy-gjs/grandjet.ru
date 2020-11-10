let rusMonth = (month) => {
    let m=null
    switch(month){
        case 0: 
        m = 'января'
        break
        case 1: 
        m =  'февраля'
        break
        case 2: 
        m =  'марта'
        case 3:  
        m = 'апреля'
        break
        case 4:  
        m = 'майя'
        break
        case 5:  
        m = 'июня'
        break
        case 6:  
        m = 'июля'
        break
        case 7:  
        m = 'августа'
        break
        case 8:  
        m = 'сентября'
        break
        case 9:  
        m = 'октяьря'
        break
        case 10: 
        m =  'ноября'
        break
        case 11: 
        m =  'декабря'
        break
}
    return m
}

var inew = 0
var irev = 0
var ipic = 3
async function getPosts()  {
    let res = await fetch('http://sportshop.loc/api/news')
    let posts = await res.json()
    document.querySelector('.news-side__items').innerHTML = ''
    posts.forEach((post)  =>{
        //console.log('обновление постa',post.date)
        let dat = new Date(post.date)
        monthNews = rusMonth(dat.getMonth())
        if(post.group === 'news' && inew < 2){
        inew++    
        document.querySelector('.news-side__items').innerHTML +=`
        <div class="news-side__item">
            <a class="news-side__label">${post.name}</a>
            <div class="news-side__body">
                <div class="news-side__data"><span>${dat.getDate()}</span>${monthNews}</div>
                <div class="news-side__text">${post.newstext}</div>
            </div>
        </div>    
        `
        }
        else if (post.group === 'reviews'  && irev < 2){
            irev++
            document.querySelector('.reviews-side__items').innerHTML +=`
            <a class="reviews-side__item">
            <div class="reviews-side__header">
                <div class="reviews-side__user">${post.name}</div>
                <div class="reviews-side__data">${dat.getDate()+'.'+ dat.getMonth() + '.' + dat.getFullYear()}</div>              
            </div>
            <div class="reviews-side__body">
            ${post.newstext}
            </div>        
        </a>

        `
        }
    } )
}

async function getPicBrends()  {
    let res = await fetch('http://sportshop.loc/api/brends')
    let pics = await res.json()
    pics.forEach((pic,index)  => {
        let el = document.getElementById('pic' + index)
        if(pic.img !== '') el.setAttribute('src','./images/' + pic.img)
    })
}

async function getTexts(){
    let i = 0
    let res = await fetch('http://sportshop.loc/api/pages/1')
    let pages = await res.json()
    let imgs = pages.hrefimage.split(';')
    let contentPage = document.querySelectorAll('.text-block__column')
    var img = document.createElement('img')
    img.setAttribute('src','../images/' + imgs[3]) 
    imgEl = document.createElement('div')
    imgEl.classList.add('text-block__image')
    imgEl.appendChild(img)
    contentPage[0].innerHTML = ''
    contentPage[1].innerHTML = ''
    elements = pages.content.split('|') 
    element = elements[0].split(';')
    
    element.forEach((txt,index)  => {
        if(txt !== '' && index < 4) {
            contentPage[0].innerHTML +=`<p> + ${txt} + </p>` 
    }
    else if(index === 4) {
        contentPage[1].innerHTML += `<h2 class="text-block__label">${txt}</h2>
        <ul class="text-block__list">`
    }
    else {
        contentPage[1].innerHTML += `<li class="text-block__list text-block__list_li-${index}">${txt}</li>`
    }
    i++
})
if(i > element.length) {
    contentPage[1].innerHTML += `</ul>`
    }
    contentPage[1].appendChild(imgEl)
}

getTexts()
getPicBrends()
getPosts()


// const id = 'men'
// let el = document.querySelector('#' + id + '13')
// console.log(el)
// let sub = []
// async function getStructure()  {
    // const lev = 0
    // 
    // let res = await fetch('http://sportshop.loc/api/structure')
    // let elements = await res.json()
    // console.log('загрузка структуры')
    // elements.forEach((elem,index)  => {
        // if(+elem.pid === lev) {
            // let el = document.querySelector('#' + id + index)
            //console.log(el)
            // if(el !== null) {
                // el.innerHTML = elem.name
                // if(elem.id > 0)getStructure(elem.id, 'submenu_')   
            // }
        // }
// 
    // })
    // 
// }
// 
// async function getBrends(){
    // let res = await fetch('http://sportshop.loc/api/brends')
    // let elements = await res.json()
    // elements.forEach((elem,index)  => {
    // if(+elem.pid === lev) {
        // let el = document.querySelector('#' + id + index)
        // el.innerHTML = elem.name
        // getStructure(elem.id, 'submenu_')   
    // }
// })
    // 
// 
// }
// getStructure().then(response => {
    // console.log(response)
// })
// let el = document.getElementById('men6')
// el.setAttribute('href',"./catalog.html/?id=1")
// console.log(el)
// 
// async function getElements()  {
    // let res = await fetch('http://sportshop.loc/api/elements')
    // let elements = await res.json()
    // elements.forEach((elem)  =>{
        // console.log(elem)
    // })
// }
// 
// async function getCardElements()  {
    // let res = await fetch('http://sportshop.loc/api/elements')
    // let elements = await res.json()
    // let AllProducts = document.querySelectorAll('.item-product__body')
    // elements.forEach((elem,index)  =>{
            // let arrname = split(elem.desc)
            // let Product = AllProducts[index]
            // Product =[ body => '<a href="" class="item-product__title"><span>'+ elem.name + '</span>'+ arrname[1] + '</a>',
        // oldprice => '<div class="item-product__oldprice">' + elem.price + '</div>',
        // price => '<div class="item-product__price">' + elem.price + '</div>'                     
        // ]
        // Product.innerHTML = Product[body] + '<div class="item-product__footer">' +
        // Product[oldprice] + '<div><a href="" class="item-product__add"><img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header"></a>'+
        // Product[price] + '</div></div></div>'
    // })
    // console.log(Product)
// }
// 
// getStructure().then(resolve => {
    // if(resolve)console.log('успешная загрузка структуры', resolve)
// }, reject => {
    // console.log('ошибка загрузки структуры', reject)
// })
// 
//getElements()