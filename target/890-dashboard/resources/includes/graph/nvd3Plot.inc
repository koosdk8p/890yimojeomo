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
        chartData.getPlot(startDate,endDate,chartName,buckets,setMetric);
    }

    function setMetric(metric){
        metrics = metric.split(',');
        if (metrics.toString() == ""){
        }
        else{
            defaultChartConfig("chart1");
        }
    }

    function defaultChartConfig(container, useGuideline) {

        if (useGuideline === undefined) useGuideline = true;

        nv.addGraph(function() {
            var chart = nv.models.scatterChart()
                    .showDistX(true)    //showDist, when true, will display those little distribution lines on the axis.
                    .showDistY(true)
                    .transitionDuration(350)
                    .color(d3.scale.category10().range());

            //Configure how the tooltip looks.
            chart.tooltipContent(function(key) {
                return '<h3>' + key + '</h3>';
            });

            //Axis settings
            chart.xAxis.tickFormat(d3.format('.02f'));
            chart.yAxis.tickFormat(d3.format('.02f'));

            //We want to show shapes other than circles.
            chart.scatter.onlyCircles(false);

            var myData = randomData();

            d3.select('#chart1 svg')
                    .datum(myData)
                    .call(chart);

            nv.utils.windowResize(chart.update);

            return chart;
        });

        function randomData() { //# groups,# points per group

            var data = [], random = d3.random.normal();

            for (i = 0; i < 1; i++) {
                data.push({
                    key: 'Group ' + i,
                    values: []
                });

                for (j = 0; j < metrics.length; j+=2) {
                    data[i].values.push({
                        x: parseInt(metrics[j+1])
                        , y: parseInt(metrics[j])
                        , size: 1   //Configure the size of each scatter point
                        , shape:"circle"  //Configure the shape of each scatter point.
                    });
                }
            }

            return data;
        }


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
                window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate );
                //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate+"&enddate="+endDate;
            }
            else{
                window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate );
                //window.location.href = window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName+"&startdate="+startDate;
            }
        }
        else{
            window.history.pushState("string", "Resonate Dashboard", window.location.origin+"/resonate-dashboard/chart?charttype=barchart&chartname="+chartName );
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
