<%--
  Created by IntelliJ IDEA.
  User: dki
  Date: 1/7/14
  Time: 3:21 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>Resonate Dashboard</title>
    <%@ include file="/resources/includes/imports.inc" %>
    <link href="<c:url value='/resources/css/bootstrap/owl.carousel.css'/>" rel="stylesheet">
    <link href="<c:url value='/resources/css/bootstrap/owl.theme.css'/>" rel="stylesheet">
    <script src="<c:url value='/resources/js/owl.carousel.js' />"></script>
    <script src="<c:url value='/resources/js/jquery-ui-1.10.4.custom.js'/>"></script>
    <link href="<c:url value='/resources/css/flick/jquery-ui-1.10.4.custom.css'/>" rel="stylesheet">


    <style>
        #owl-demo .item img{
            display: block;
            width: 80%;
            height: auto;
        }
    </style>
    <script>
        $(document).ready(function() {
            $("#owl-demo").owlCarousel({

                navigation : true,
                slideSpeed : 300,
                paginationSpeed : 400,
                singleItem : true

                // "singleItem:true" is a shortcut for:
                // items : 1,
                // itemsDesktop : false,
                // itemsDesktopSmall : false,
                // itemsTablet: false,
                // itemsMobile : false

            });
        });
    </script>



</head>
<body class='with-3d-shadow with-transitions'>
    <%@ include file="/resources/includes/header.inc" %>
    <%@ include file="/resources/includes/sidebarnvd3.inc" %>
    <div class="page-body" roll="main" id="status-main" style="float: left; width: 55%; padding-top: 7em;">
            <div id="owl-demo" class="owl-carousel">
                <div class="item"><img src="<c:url value='/resources/images/carousel/main1.JPG' />" alt="Carousel1"></div>
                <div class="item"><img src="<c:url value='/resources/images/carousel/main3.JPG' />" alt="Carousel3"></div>
                <div class="item"><img src="<c:url value='/resources/images/carousel/main5.JPG' />" alt="Carousel5"></div>
                <div class="item"><img src="<c:url value='/resources/images/carousel/main6.JPG' />" alt="Carousel6"></div>
            </div>
    </div>
    <%@ include file="/resources/includes/footer.inc" %>
</body>
</html>

