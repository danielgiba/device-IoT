import com.arrowhead.client.ArrowheadClient;
import com.microsoft.sqlserver.jdbc.SQLServerDataSource;
import com.microsoft.sqlserver.jdbc.SQLServerException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ArrowheadStoreBD {

    public static void main(String[] args) {
        ArrowheadClient arrowheadClient = new ArrowheadClient();

        SQLServerDataSource dataSource = new SQLServerDataSource();
        dataSource.setServerName("localhost");
        dataSource.setDatabaseName("prepractica");
        dataSource.setUser("sa");
        dataSource.setPassword("pass");

        try (Connection conn = dataSource.getConnection()) {
            String insertQuery = "INSERT INTO temperatura (idSenzor, temperatura, umiditate) VALUES (2, 23.7 0)";
            try (PreparedStatement stmt = conn.prepareStatement(insertQuery)) {
                stmt.setString(1, "senzor123");
                stmt.setFloat(2, 23.5f);
                stmt.setFloat(3, 60.2f);
                stmt.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            }
            
            arrowheadClient.storeData("temperatura", "senzorTemp", "23.5");

        } catch (SQLServerException | SQLException e) {
            e.printStackTrace();
        }
    }
}
