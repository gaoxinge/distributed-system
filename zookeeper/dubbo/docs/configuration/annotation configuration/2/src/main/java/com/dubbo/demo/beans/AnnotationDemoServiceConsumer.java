package com.dubbo.demo.beans;

import com.alibaba.dubbo.config.annotation.Reference;
import com.dubbo.demo.DemoService;
import org.springframework.stereotype.Component;

@Component
public class AnnotationDemoServiceConsumer {

    @Reference
    private DemoService demoService;

    public String doSayHello(String name) {
        return demoService.sayHello(name);
    }
}
