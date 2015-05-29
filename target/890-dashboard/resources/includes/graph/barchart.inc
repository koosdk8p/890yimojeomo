<script type="text/javascript" src="//www.google.com/jsapi"></script>
<script type="text/javascript">
google.load('visualization', '1', {packages: ['corechart']});
</script>
<script type="text/javascript">

google.setOnLoadCallback(loadMetric);

//today = new Date();
//lastMonth = new Date();
//lastMonth.setMonth(lastMonth.getMonth()-1);


//startDate = lastMonth.getFullYear() + "-" + ("0" + (lastMonth.getMonth()+1)).slice(-2) + "-" + ("0" + lastMonth.getDate()).slice(-2);
//endDate = today.getFullYear() + "-" + ("0" + (today.getMonth()+1)).slice(-2) + "-" + ("0" + today.getDate()).slice(-2);
//chartName = "com.resonate.stitching.addthis.rcid.distribution";


function loadMetric(){
    chartData.getCount(startDate,endDate,chartName,buckets,drawChart);
}

function drawChart(counts) {
    // Create and populate the data table.
    //var data = google.visualization.arrayToDataTable(distribution);

    var metric = JSON.parse(counts);

    if (counts != "1"){
        var data = google.visualization.arrayToDataTable(metric);
    }

    // Create and draw the visualization.
    if (counts != "1"){
        new google.visualization.BarChart(document.getElementById('visualization')).
                draw(data,
                {title:chartName,
                    width:800, height:400,
                    vAxis: {title: "Date"},
                    hAxis: {title: "Counts"}}
        );
    }
}


<!-- Date picker related scripts -->

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
        alert("Start Date Not Set!");
    }
    if (endDate == ""){
        alert("End Date Not Set!");
    }
    loadMetric();
}


</script>

<script type="text/javascript">
$(document).ready(function() {
    chartName = "<c:out value='${chartName}' />";
    startDate = "<c:out value='${startDate}' />";
    endDate = "<c:out value='${endDate}' />";
    buckets = "<c:out value='${buckets}' />";
    loadMetric();
});

</script>