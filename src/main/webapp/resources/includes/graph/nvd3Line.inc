<link rel="stylesheet" href='<c:url value="/resources/css/d3/nv.d3.css" />' type="text/css" />
<script src='<c:url value="/resources/js/d3/d3.js" />' ></script>
<script src='<c:url value="/resources/js/d3/nv.d3.js"/>'></script>
<style>
body {
    overflow-y:scroll;
}
text {
    font: 12px sans-serif;
}
svg {
    display: block;
}
#chart1 svg {
    height: 500px;
    min-width: 200px;
    min-height: 100px;
    /*
      margin: 50px;
      Minimum height and width is a good idea to prevent negative SVG dimensions...
      For example width should be =< margin.left + margin.right + 1,
      of course 1 pixel for the entire chart would not be very useful, BUT should not have errors
    */
}
#chart1 {
    margin-top: 50px;
    margin-left: 10px;
}
</style>

<script>

/*Data sample:
 {
 "key" : "North America" ,
 "values" : [ [ 1025409600000 , 23.041422681023] , [ 1028088000000 , 19.854291255832],
 [ 1030766400000 , 21.02286281168],
 [ 1033358400000 , 22.093608385173],
 [ 1036040400000 , 25.108079299458],
 [ 1038632400000 , 26.982389242348]
 ...

 */

//an example of harmonizing colors between visualizations
//observe that Consumer Discretionary and Consumer Staples have
//been flipped in the second chart
var colors = d3.scale.category20();
var keyColor = function(d, i) { return colors(d.key)};
var metrics;

function loadMetric(){
    chartData.getCount(startDate,endDate,chartName,buckets,setMetric);
}

function setMetric(metric){
    metrics = "[" + metric + "]";
    metrics = eval(metrics);
    if (metrics.toString() == ""){
    }
    else{
        defaultChartConfig("chart1");
    }
}

function defaultChartConfig(container, useGuideline) {
    if (useGuideline === undefined) useGuideline = true;

    data = metrics;

    nv.addGraph(function() {
        var chart = nv.models.stackedAreaChart()
                .margin({right: 100})
                .x(function(d) { return d[0] })   //We can modify the data accessor functions...
                .y(function(d) { return d[1] })   //...in case your data is formatted differently.
                .useInteractiveGuideline(true)    //Tooltips which show all data points. Very nice!
                .rightAlignYAxis(true)      //Let's move the y-axis to the right side.
                .transitionDuration(500)
                .showControls(true)       //Allow user to choose 'Stacked', 'Stream', 'Expanded' mode.
                .clipEdge(true);

        //Format x-axis labels with custom function.
        chart.xAxis
                .tickFormat(function(d) {
                    return d3.time.format('%x')(new Date(d))
                });

        chart.yAxis
                .tickFormat(d3.format(',.2f'));

        d3.select('#chart1 svg')
                .datum(data)
                .call(chart);

        nv.utils.windowResize(chart.update);

        return chart;
    });
}
</script>


<!-- Date picker related scripts -->
<script>
$(function() {
    $( "#startRange").datepicker({
        inline: true,
        dateFormat: 'yy-mm-dd'
    });
});

$(function() {
    $( "#endRange").datepicker({
        inline: true,
        dateFormat: 'yy-mm-dd'
    });
});

function buttonClick(){
    startDate = $("#startRange").datepicker().val();
    endDate = $("#endRange").datepicker().val();

    if (startDate == ""){
        //alert("Start Date Not Set!");
    }
    if (endDate == ""){
        //alert("End Date Not Set!");
    }

    if (startDate != ""){
        if (endDate != ""){
            window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=linechart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate );
            //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate;
        }
        else{
            window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=linechart&chartname="+chartName+"&startdate="+startDate );
            //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate;
        }
    }
    else{
        window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=linechart&chartname="+chartName );
    }
    //displayName = chartData.getDisplayName(chartName);
    //alert(displayName);
    loadMetric();
}


$(document).ready(function() {
    chartName = "<c:out value='${chartName}' />";
    startDate = "<c:out value='${startDate}' />";
    endDate = "<c:out value='${endDate}' />";
    buckets = "<c:out value='${buckets}' />";
    getDisplayName();
    getChartDescription();
    loadMetric();

});

function getDisplayName(){
    chartData.getDisplayName(chartName,setDisplayName);
}
function setDisplayName(displayName){
    document.getElementById("chartName").innerHTML=displayName;
}

function getChartDescription(){
    chartData.getChartDescription(chartName,setChartDescription);
}
function setChartDescription(chartDescription){
    document.getElementById("chartDescription").innerHTML=chartDescription;
}

</script>