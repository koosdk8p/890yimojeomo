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
        var chart;

        chart = nv.models.multiBarChart()
                .x(function(d) { return d[0]  })
                .y(function(d) { return d[1] })
                .color(keyColor)
                .margin({bottom: 100})
                .transitionDuration(500)

        ;


        var chartOptions =
        {
            delay: 0,
            transitionDuration:500,
            groupSpacing: 0.2

        };
        chart.margin({left: 100})
        chart.options(chartOptions);
        chart.multibar
                .hideable(true);

        chart.xAxis
                .axisLabel("Date")
                .showMaxMin(true)
                .tickFormat(function(d) { return d3.time.format('%x')(new Date(d)) });

        chart.yAxis
                .tickFormat(d3.format(','));


        d3.select('#chart1 svg')
                .datum(data)
                .call(chart);

        nv.utils.windowResize(chart.update);


        return chart;
    });
//  });
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

    var SelectedOptions = document.getElementById("counts");
    chartName = "{";
    for (var i=0;i<SelectedOptions.length;i++) {
        if (SelectedOptions.options[i].selected) {
            chartName += SelectedOptions.options[i].value + ","
        }
    }
    chartName = chartName.substring(0, chartName.length -1);
    chartName += "}";


    if (startDate == ""){
        //alert("Start Date Not Set!");
    }
    if (endDate == ""){
        //alert("End Date Not Set!");
    }
    if (startDate != ""){
        if (endDate != ""){
            window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/group?charttype=barchart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate );
            //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate;
        }
        else{
            window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/group?charttype=barchart&chartname="+chartName+"&startdate="+startDate );
            //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate;
        }
    }
    else {
        window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/group?charttype=barchart&chartname="+chartName);
    }
    loadMetric();
}


$(document).ready(function() {
    chartName = "<c:out value='${chartName}' />";
    startDate = "<c:out value='${startDate}' />";
    endDate = "<c:out value='${endDate}' />";
    buckets = "<c:out value='${buckets}' />";
    //document.getElementById("chartName").innerHTML=chartName;
    loadMetric();

});
</script>
