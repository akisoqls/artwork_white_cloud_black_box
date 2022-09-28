window.addEventListener('resize', () => {
  document.getElementById('eyecatch').style.height = `${window.innerHeight - document.getElementById('properties').clientHeight}px`
})