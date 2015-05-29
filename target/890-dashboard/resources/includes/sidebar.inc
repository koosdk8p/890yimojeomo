<script type="text/javascript" src="jquery.cookie.js">
<script type="text/javascript">

    jQuery(document).ready(function(){

        //target the class 'accordion-body'
        jQuery('.accordion-body').on('shown', function(e){

            //save the uncollapsed/shown item ID to your cookie:
            jQuery.cookie('cookie_collapse', jQuery(e.target).attr('id'));
        });

        var lastCollapse = jQuery.cookie('cookie_collapse');

        //if the cookie exists:-
        //activate uncollapsed item by adding the class 'in' to the saved ID
        if (lastCollapse) {
            var lastCollapse = '#' + lastCollapse
            jQuery(lastCollapse).addClass('in');
        }
    } );

</script>

<div id="status" role="complementary" style="float: left; width: 22%" xmlns:g="http://www.w3.org/1999/xhtml">
    <h1>Resonate Dashboard</h1>
    <ul>
            <li class="controller">
                <div class="accordion-group">
                    <div class="accordion-heading">
                        <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion2" href="#menu">
                            Metrics
                        </a>
                    </div>
                    <div id="menu" class="accordion-body collapse">
                        <div class="accordion-inner show">
                            <div id="tab">
                                <font color="#48802C">AddThis</font>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.addthis.rcid.distribution' />">Unique AddThis to RCID Stitches</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.rcid.addthis.distribution' />">Unique RCID to AddThis Stitches</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.behavior.addthis.raw.id.count' />">AddThis Behavior ID Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.behavior.addthis.raw.record.count' />">AddThis Behavior Record Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.addthis.record.count' />">AddThis Stitching Total Record Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.addthis.rcid.count' />">AddThis Unique RCID Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.addthis.vendor.distribution' />">AddThis Vendor Distribution</a></div>
                                <font color="#48802C">LiveRamp</font>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.liveramp.record.count' />">Liveramp Stitching Record Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.liveramp.rcid.count' />">Liveramp Stitching RCID Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.liveramp.vendor.distribution' />">Liveramp Vendor Distribution</a></div>
                                <font color="#48802C">Model</font>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.modelqueue.domain.distribution' />">Modelqueue Domain Distribution</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.modelqueue.hitcount.distribution' />">Modelqueue Hitcount Distribution</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.modelqueue.timespan.distribution' />">Modelqueue Timespan Distribution</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.modelqueue.rcid.count' />">Modelqueue Rcid Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.rcid.mediamath.modeled.count' />">RCID-MediaMath Modeled Count</a></div>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.stitching.rcid.tubemogul.modeled.count' />">RCID-TubeMogul Modeled Count</a></div>
                                <font color="#48802C">CookieJar</font>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.modeling.cookiejarsize' />">Daily Cookiejar Size</a></div>
                                <font color="#48802C">Other</font>
                                <div id="tab"><a href="<c:url value='/chart?charttype=barchart&chartname=com.resonate.pixels.type.distribution' />">Pixel Type Distribution</a></div>
                                <font color="#48802C">Grouping</font>
                                <div id="tab"><a href="<c:url value='/group' />">Counts Grouper</a></div>
                            </div>
                        </div>
                    </div>
                </div>
            </li>
            <li class="controller">
                <div class="accordion-group">
                    <div class="accordion-heading">
                        <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion2" href="#collapseTwo">
                            Files
                        </a>
                    </div>
                    <div id="collapseTwo" class="accordion-body collapse">
                        <div class="accordion-inner">

                        </div>
                    </div>
                </div>
            </li>
        <li class="controller">
            <div class="accordion-group">
                <div class="accordion-heading">
                    <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion2" href="#collapseThree">
                        Pixel Distribution
                    </a>
                </div>
                <div id="collapseThree" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <div id="tab"><a href="<c:url value='/pixeldistribution' />">U.S. Pixel Distribution</a></div>
                    </div>
                </div>
            </div>
        </li>
    </ul>
        <div id="tab"><a href="<c:url value='/tetris' />"><font color="#ddd">Secret</font></a></div>
</div>
