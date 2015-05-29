<!--Load the AJAX API for Google chart tool-->
<script type="text/javascript" src="https://www.google.com/jsapi"></script>
<script type="text/javascript">
// Load the Visualization API and the piechart package.
google.load('visualization', '1.0', {'packages':['corechart']});

// Set a callback to run when the Google Visualization API is loaded.
google.setOnLoadCallback(loadMetric);

//today = new Date();
//lastMonth = new Date();
//lastMonth.setMonth(lastMonth.getMonth()-1);
//startDate = lastMonth.getFullYear() + "-" + ("0" + (lastMonth.getMonth()+1)).slice(-2) + "-" + ("0" + lastMonth.getDate()).slice(-2);
//endDate = today.getFullYear() + "-" + ("0" + (today.getMonth()+1)).slice(-2) + "-" + ("0" + today.getDate()).slice(-2);
//chartName = "com.resonate.stitching.addthis.rcid.distribution";


function loadMetric(){
    chartData.getDistributionSum(startDate,endDate,chartName,rules,drawChart);
}

// Callback that creates and populates a count table,
// instantiates the pie chart, passes in the count and
// draws it.
function drawChart(distributions) {
    var metric = JSON.parse(distributions);

    // Create the count table.
    var data = new google.visualization.DataTable();
    data.addColumn('string', 'Stitches');
    data.addColumn('number', 'Percentage');
    data.addRows(metric);

    // Set chart options
    var options = {'title':chartName,
        'width':800,
        'height':400,
        is3D: true};

    // Instantiate and draw our chart, passing in some options.
    var chart = new google.visualization.PieChart(document.getElementById('chart_div'));

    chart.draw(data, options);
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

<!-- Chart selection scripts          -->
/*$(document).ready(function() {
    $('select').change(function() {
        startDate = $("#startRange").datepicker().val();
        endDate = $("#endRange").datepicker().val();
        if (startDate == ""){
            alert("Start Date Not Set!");
        }
        if (endDate == ""){
            alert("End Date Not Set!");
        }
        chartName = $(this).val();
        loadMetric();

    });
});
*/

</script>
<script type="text/javascript">
$(document).ready(function() {
    chartName = "<c:out value='${chartName}' />";
    startDate = "<c:out value='${startDate}' />";
    endDate = "<c:out value='${endDate}' />";
    rules = "<c:out value='${rules}' />";
    loadMetric();
});

</script>