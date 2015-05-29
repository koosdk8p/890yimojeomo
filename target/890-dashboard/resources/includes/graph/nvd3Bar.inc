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

    //metrics1 = [{"key":"com.resonate.modelqueue.rcid.count","values":[[1388566800000,3730232],[1388653200000,3338911],[1388739600000,4276293],[1388826000000,4370720],[1388912400000,3471341],[1388998800000,3686502],[1389085200000,5086821],[1389171600000,4756569],[1389258000000,4067971],[1389344400000,3867842],[1389430800000,4408606],[1389517200000,3727456],[1389603600000,3660360],[1389690000000,5019930],[1389776400000,4635472],[1389862800000,3956233],[1389949200000,3756353],[1390035600000,4262969],[1390122000000,3552781],[1390208400000,3565077],[1390294800000,4638428],[1390381200000,5075304],[1390467600000,4102361],[1390554000000,3892494],[1390640400000,11739672],[1390726800000,3949649],[1390813200000,4104310],[1390899600000,5757637],[1390986000000,4651764],[1391072400000,4395557],[1391158800000,5386373],[1391245200000,4440804],[1391331600000,4238398],[1391418000000,6194569],[1391504400000,7545477],[1391590800000,6152197],[1391677200000,5279182],[1391763600000,4732931],[1391850000000,4816371],[1391936400000,4416073],[1392022800000,4357361],[1392109200000,6221269],[1392195600000,4718753],[1392282000000,4110910],[1392368400000,12743975],[1392454800000,5317372],[1392541200000,3584022],[1392627600000,3055152],[1392714000000,3996546],[1392800400000,3563978],[1392886800000,9199087],[1392973200000,5461525],[1393059600000,4005293],[1393146000000,3330528],[1393232400000,3359294],[1393318800000,4583381],[1393405200000,7554362],[1393491600000,5579018],[1393578000000,4484580],[1393664400000,3641207],[1393750800000,3400824],[1393837200000,3520983],[1393923600000,7652775],[1394010000000,5855979],[1394096400000,4816758],[1394182800000,3920789],[1394269200000,3568331],[1394355600000,3349718],[1394355600000,3349718],[1394442000000,4731539],[1394528400000,10889258],[1394614800000,7074142],[1394701200000,5664752],[1394787600000,4743091],[1394874000000,3962347],[1394960400000,4654301],[1395046800000,6192891],[1395133200000,9088908],[1395219600000,6519972],[1395306000000,5530563],[1395392400000,4665299],[1395478800000,4805067],[1395565200000,5198736],[1395651600000,5692082],[1395738000000,9136090],[1395824400000,6574459]]}];
    //metrics = [{"key":"com.resonate.modelqueue.rcid.count","values":[[1388566800000,3730232],[1388653200000,3338911],[1388739600000,4276293],[1388826000000,4370720],[1388912400000,3471341],[1388998800000,3686502],[1389085200000,5086821],[1389171600000,4756569],[1389258000000,4067971],[1389344400000,3867842],[1389430800000,4408606],[1389517200000,3727456],[1389603600000,3660360],[1389690000000,5019930],[1389776400000,4635472],[1389862800000,3956233],[1389949200000,3756353],[1390035600000,4262969],[1390122000000,3552781],[1390208400000,3565077],[1390294800000,4638428],[1390381200000,5075304],[1390467600000,4102361],[1390554000000,3892494],[1390640400000,11739672],[1390726800000,3949649],[1390813200000,4104310],[1390899600000,5757637],[1390986000000,4651764],[1391072400000,4395557],[1391158800000,5386373],[1391245200000,4440804],[1391331600000,4238398],[1391418000000,6194569],[1391504400000,7545477],[1391590800000,6152197],[1391677200000,5279182],[1391763600000,4732931],[1391850000000,4816371],[1391936400000,4416073],[1392022800000,4357361],[1392109200000,6221269],[1392195600000,4718753],[1392282000000,4110910],[1392368400000,12743975],[1392454800000,5317372],[1392541200000,3584022],[1392627600000,3055152],[1392714000000,3996546],[1392800400000,3563978],[1392886800000,9199087],[1392973200000,5461525],[1393059600000,4005293],[1393146000000,3330528],[1393232400000,3359294],[1393318800000,4583381],[1393405200000,7554362],[1393491600000,5579018],[1393578000000,4484580],[1393664400000,3641207],[1393750800000,3400824],[1393837200000,3520983],[1393923600000,7652775],[1394010000000,5855979],[1394096400000,4816758],[1394182800000,3920789],[1394269200000,3568331],[1394355600000,3349718],[1394355600000,3349718],[1394442000000,4731539],[1394528400000,10889258],[1394614800000,7074142],[1394701200000,5664752],[1394787600000,4743091],[1394874000000,3962347],[1394960400000,4654301],[1395046800000,6192891],[1395133200000,9088908],[1395219600000,6519972],[1395306000000,5530563],[1395392400000,4665299],[1395478800000,4805067],[1395565200000,5198736],[1395651600000,5692082],[1395738000000,9136090],[1395824400000,6574459]]}];



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

       if (chartName != "") {
           getDisplayName();
           getChartDescription();
       }
        loadMetric();

   });

   function getDisplayName(){
       chartData.getDisplayName(chartName,setDisplayName);
   }
   function setDisplayName(displayName){
        document.getElementById("chartName").innerHTML = displayName;
   }

   function getChartDescription(){
       chartData.getChartDescription(chartName,setChartDescription);
   }
   function setChartDescription(chartDescription){
        document.getElementById("chartDescription").innerHTML = chartDescription;

   }

   function nextgenbuttonClick(){
       startDate = $("#startRange").datepicker().val();
       endDate = $("#endRange").datepicker().val();
       audienceKey = document.getElementById("audience").value;

       var e = document.getElementById("counts");
       chartName = e.options[e.selectedIndex].value + audienceKey;

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

</script>
