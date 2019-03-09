package gxg.beans;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class Comp1 {
    @Bean
    public TestBean testBean() {
        return new TestBean();
    }
}
