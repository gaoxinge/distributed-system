package org.apache.dubbo.samples.server;

import com.alibaba.dubbo.config.ApplicationConfig;
import com.alibaba.dubbo.config.RegistryConfig;
import com.alibaba.dubbo.config.ServiceConfig;
import org.apache.dubbo.samples.api.GreetingService;

import java.io.IOException;

public class Application {
    public static void main(String[] args) throws IOException {
        ServiceConfig<GreetingService> service = new ServiceConfig<>();
        service.setApplication(new ApplicationConfig("first-dubbo-provider"));
        service.setRegistry(new RegistryConfig("zookeeper://127.0.0.1:2181"));
        service.setInterface(GreetingService.class);
        service.setRef(new GreetingServiceImpl());
        service.export();
        System.out.println("first-dubbo-provider is running.");
        System.in.read();
    }
}
