package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.FlightModel;
import com.flightmanager.databaseservice.repos.FlightRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
public class FlightController {

    @Autowired
    private FlightRepo repo;

    @GetMapping("${mapping.flight.get}/{id}")
    public ResponseEntity<FlightModel> get(@PathVariable("id") long id) {
        try{
            FlightModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.flight.create}")
    public ResponseEntity<FlightModel> get(@RequestBody FlightModel data) {
        try{
            data.setId(0L);
            FlightModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.flight.update}")
    public ResponseEntity<FlightModel> update(@RequestBody FlightModel data) {
        try{
            if(repo.findById(data.getId()).orElse(null) == null)
                return ResponseEntity.status(400).build();
            FlightModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.flight.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

}
