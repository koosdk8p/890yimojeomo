package com.springapp.mvc;

import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/chart")
public class ChartController {
	@RequestMapping(method = RequestMethod.GET)
	public String returnChart(ModelMap model, @RequestParam(value = "charttype", required = false) String chartType,
							  @RequestParam(value = "chartname", required = false) String chartName,
							  @RequestParam(value = "startdate", required = false) String startDate,
							  @RequestParam(value = "enddate", required = false) String endDate){


		model.addAttribute("chartType",chartType);
		model.addAttribute("chartName",chartName);
		model.addAttribute("startDate",startDate);
		model.addAttribute("endDate",endDate);

		return "/graph";
	}
}