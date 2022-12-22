var canvas = document.querySelector('canvas');
var c = canvas.getContext('2d');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

//create empty array
var images = [];
images.length = 10;

//push the images into array


async function getData(){
    for(var i = 1 ; i < images.length ; i++){
        images[i] = new Image();
        //images[i].src = 'Walk (' + i.toString() + ').png';
    
      await  fetch('https://mehmetak7.github.io/mehmetak/HWimages/'+'Walk (' + i.toString() + ').png').then(res=>res.blob())
                                                 .then(blob => {
                                                    let objectURL = URL.createObjectURL(blob);
                                                    images[i].src = objectURL;
                                                 });
    }

}

getData();


var i = 1;
var y = 0;
var test;

var kontrol=0;

btnPause.addEventListener("click", function(){
    if(kontrol==0){
    clearInterval(test);
        kontrol=1;
    }
    else{
        test = setInterval(function(){
            i++;
            y++;
            if( i >= 10){
                i = 1;
            }
            if(y<10){
               // console.log(images[i]);
            }
            c.drawImage(images[i],275,275,275,275);
        },150)
        kontrol=0;
    }
});

btnStop.addEventListener("click", function(){
    clearInterval(test);
});

btnNext.addEventListener("click", function(){
    i++;
    if(i == 10){
        i =1;
    }
    c.drawImage(images[i],275,275,275,275);
});

btnPrev.addEventListener("click", function(){
    i--;
    if(i == 0){
        i = 10;
    }
    c.drawImage(images[i],275,275,275,275);
});

btnStart.addEventListener("click", function(){
    i=1;
    test = setInterval(function(){
        i++;
        y++;
        if( i >= 10){
            i = 1;
        }
        if(y<10){
           // console.log(images[i]);
        }
        c.drawImage(images[i],275,275,275,275);
    },150)
});

