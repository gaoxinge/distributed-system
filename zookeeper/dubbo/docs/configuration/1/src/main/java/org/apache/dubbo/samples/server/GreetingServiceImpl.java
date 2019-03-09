package org.apache.dubbo.samples.server;

import org.apache.dubbo.samples.api.GreetingService;

public class GreetingServiceImpl implements GreetingService {
    @Override
    public String sayHi(String name) {
        return "hi, " + name;
    }
}
