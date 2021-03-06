<link rel="stylesheet" href='<c:url value="/resources/css/d3/nv.d3.css" />' type="text/css" />
<script src='<c:url value="/resources/js/d3/d3.js" />' ></script>
<script src='<c:url value="/resources/js/d3/nv.d3.js"/>'></script>

<div id="status" role="complementary" style="float: left; width: 34%" xmlns:g="http://www.w3.org/1999/xhtml">
    <div id="chart"></div>

</div>

<script>

var menuData;
function fetchMenu(){
    chartData.getMenu(loadMenu);
}

function loadMenu(menu){
    alert(menu);
    menuData = eval(menu);



    nv.addGraph(function() {
    var chart = nv.models.indentedTree()
    .tableClass('table table-striped') //for bootstrap styling
    .columns([
    {
        key: 'key',
        label: '890-dashboard',
        showCount: false,
        width: '65%',
        type: 'text',
        classes: function(d) { return d.url ? 'clickable name' : 'name' },
        click: function(d) {
            if (d.url) window.location.href = d.url;
    }}]);


    d3.select('#chart')
    .datum(menuData)
    .call(chart);

    return chart;
    });
}


$(document).ready(function() {
    fetchMenu();
});
</script>
